#include "handler.hpp"

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "game_manager.hpp"
#include <json/json.hpp>
#include <skynet/checkers.hpp>
#include <skynet/neuralnet.hpp>

extern game_manager_t global_game_manager;

http_header_t get_header(const http_message& message)
{
	http_header_t header;

	for(int ii=0;ii<MG_MAX_HTTP_HEADERS;++ii)
	{
		std::string key(message.header_names[ii].p,message.header_names[ii].len);
		std::string value(message.header_values[ii].p,message.header_values[ii].len);

		if(key=="")
			break;

		header[key]=value;
	}

	return header;
}

std::string get_query(const mg_str* query_string,const std::string& var)
{
	std::string temp;
	temp.resize(100);
	int size=mg_get_http_var(query_string,var.c_str(),(char*)temp.c_str(),temp.size());

	if(size<0)
		size=0;

	temp.resize(size);
	return temp;
}

void mg_send(mg_connection* connection,const std::string& data,const std::string& mime)
{
	mg_printf(connection,"HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %ld\r\n\r\n%s",
		mime.c_str(),data.size(),data.c_str());
}

void mg_send_status(mg_connection* connection,const std::string& status)
{
	mg_printf(connection,"HTTP/1.1 %s\r\nContent-Length: 0\r\n\r\n\r\n\r\n",status.c_str());
}

void eval_handler(mg_connection* connection,int event,const std::string& post_data)
{
	try
	{
		json_t json=JSON_parse(post_data);

		if(!json.isObject())
			throw std::runtime_error("Not a JSON object.");

		auto inputs=to_double_array(json["inputs"]);
		auto layers=to_size_array(json["layers"]);
		auto weights=to_double_array(json["weights"]);
		size_t sigmoid_index=json["sigmoid_index"].asUInt();
		double a=1;
		double b=1;
		double c=0;

		if(json["a"].isDouble())
			a=json["a"].asDouble();
		else
			throw std::runtime_error("Constant \"a\" is not a float.");
		if(json["b"].isDouble())
			b=json["b"].asDouble();
		else
			throw std::runtime_error("Constant \"b\" is not a float.");
		if(json["c"].isDouble())
			c=json["c"].asDouble();
		else
			throw std::runtime_error("Constant \"c\" is not a float.");

		skynet::neuralnet_t neuralnet(layers,weights);

		if(inputs.size()!=layers[0])
			throw std::runtime_error("Invalid number of inputs(expected "+std::to_string(layers[0])+" got "+std::to_string(inputs.size())+").");

		int times=100000;
		auto start=std::chrono::system_clock::now();
		double output=0;

		for(auto ii=0;ii<times;++ii)
			output=neuralnet.evaluate(inputs,sigmoid_index,a,b,c);

		auto end=std::chrono::system_clock::now();
		auto time=std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count()/(double)times;

		mg_send(connection,"{\"output\":"+std::to_string(output)+",\"ns\":"+std::to_string(time)+"}","application/json");
	}
	catch(std::exception& error)
	{
		json_t json;
		json["error"]=error.what();
		mg_send(connection,JSON_serialize(json),"application/json");
	}
	catch(...)
	{
		json_t json;
		json["error"]="Could not parse JSON object.";
		mg_send(connection,JSON_serialize(json),"application/json");
	}
}

void move_generator_handler(mg_connection* connection,int event,const std::string& post_data)
{
	try
	{
		json_t json=JSON_parse(post_data);

		if(!json.isObject())
			throw std::runtime_error("Not a JSON object.");

		skynet::checkers::board_t board=json["board"].asString();

		std::string player_raw(json["player"].asString());
		skynet::checkers::player_t player=skynet::checkers::player_from_string(player_raw);

		int times=100000;
		auto start=std::chrono::system_clock::now();
		skynet::checkers::board_list_t moves;

		for(auto ii=0;ii<times;++ii)
			moves=skynet::checkers::move_generator(board,player);

		auto end=std::chrono::system_clock::now();
		auto time=std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count()/(double)times;

		mg_send(connection,"{\"moves\":"+std::to_string(moves)+",\"ns\":"+std::to_string(time)+"}","application/json");
	}
	catch(std::exception& error)
	{
		json_t json;
		json["error"]=error.what();
		mg_send(connection,JSON_serialize(json),"application/json");
	}
	catch(...)
	{
		json_t json;
		json["error"]="Could not parse JSON object.";
		mg_send(connection,JSON_serialize(json),"application/json");
	}
}

void list_games_handler(mg_connection* connection,int event,const std::string& post_data)
{
	try
	{
		mg_send(connection,std::to_string(global_game_manager.list()),"application/json");
	}
	catch(std::exception& error)
	{
		json_t json;
		json["error"]=error.what();
		mg_send(connection,JSON_serialize(json),"application/json");
	}
	catch(...)
	{
		json_t json;
		json["error"]="Could not parse JSON object.";
		mg_send(connection,JSON_serialize(json),"application/json");
	}
}

void create_game_handler(mg_connection* connection,int event,const std::string& post_data)
{
	try
	{
		json_t json=JSON_parse(post_data);

		if(!json.isObject())
			throw std::runtime_error("Not a JSON object.");

		global_game_manager.create_game(json["name"].asString());
		mg_send(connection,"{}","application/json");
	}
	catch(std::exception& error)
	{
		json_t json;
		json["error"]=error.what();
		mg_send(connection,JSON_serialize(json),"application/json");
	}
	catch(...)
	{
		json_t json;
		json["error"]="Could not parse JSON object.";
		mg_send(connection,JSON_serialize(json),"application/json");
	}
}

void info_game_handler(mg_connection* connection,int event,const std::string& post_data)
{
	try
	{
		json_t json=JSON_parse(post_data);

		if(!json.isObject())
			throw std::runtime_error("Not a JSON object.");

		skynet::checkers::game_info_t info=global_game_manager.info_game(json["name"].asString());
		mg_send(connection,std::to_string(info),"application/json");
	}
	catch(std::exception& error)
	{
		json_t json;
		json["error"]=error.what();
		mg_send(connection,JSON_serialize(json),"application/json");
	}
	catch(...)
	{
		json_t json;
		json["error"]="Could not parse JSON object.";
		mg_send(connection,JSON_serialize(json),"application/json");
	}
}

void play_game_handler(mg_connection* connection,int event,const std::string& post_data)
{
	try
	{
		json_t json=JSON_parse(post_data);

		if(!json.isObject())
			throw std::runtime_error("Not a JSON object.");

		std::string name=json["name"].asString();
		std::string board=json["board"].asString();

		global_game_manager.play_game(name,board);
		mg_send(connection,"{}","application/json");
	}
	catch(std::exception& error)
	{
		json_t json;
		json["error"]=error.what();
		mg_send(connection,JSON_serialize(json),"application/json");
	}
	catch(...)
	{
		json_t json;
		json["error"]="Could not parse JSON object.";
		mg_send(connection,JSON_serialize(json),"application/json");
	}
}

void client_handler(mg_connection* connection,int event,void* event_data)
{
	if(event==MG_EV_HTTP_REQUEST)
	{
		mg_serve_http_opts* options=(mg_serve_http_opts*)(connection->mgr->user_data);

		if(options==nullptr)
			throw std::runtime_error("HTTP options was null.");

		http_message* message=(http_message*)event_data;

		if(message==nullptr)
			throw std::runtime_error("HTTP message was null.");

		char client_raw[200];
		mg_sock_to_str(connection->sock,client_raw,200,MG_SOCK_STRINGIFY_IP);
		std::string client(client_raw);

		http_header_t header=get_header(*message);

		if(client=="127.0.0.1")
			for(auto pair:header)
				if(pair.first=="X-Forwarded-For")
					client=pair.second;

		std::string method(message->method.p,message->method.len);
		std::string request(message->uri.p,message->uri.len);
		std::string query(message->query_string.p,message->query_string.len);
		std::string post_data(message->body.p,message->body.len);

		std::cout<<client<<std::flush;
		if(client==std::string(client_raw))
			std::cout<<" NOLOOKUP";
		else
			std::cout<<" LOOKUP  ";
		std::cout<<" "<<method<<" "<<request<<"."<<std::endl;
		std::cout<<"\tQuery:  \""<<query<<"\""<<std::endl;

		if(method=="POST")
			std::cout<<"\tPost:  \""<<post_data<<"\""<<std::endl;

		std::string is_eval=get_query(&message->query_string,"eval");
		std::string is_move_generator=get_query(&message->query_string,"move_generator");
		std::string is_list_games=get_query(&message->query_string,"list_games");
		std::string is_create_game=get_query(&message->query_string,"create_game");
		std::string is_info_game=get_query(&message->query_string,"info_game");
		std::string is_play_game=get_query(&message->query_string,"play_game");

		if(is_eval!=""&&is_eval!="false")
			eval_handler(connection,event,post_data);
		else if(is_move_generator!=""&&is_move_generator!="false")
			move_generator_handler(connection,event,post_data);
		else if(is_list_games!=""&&is_list_games!="false")
			list_games_handler(connection,event,post_data);
		else if(is_create_game!=""&&is_create_game!="false")
			create_game_handler(connection,event,post_data);
		else if(is_info_game!=""&&is_info_game!="false")
			info_game_handler(connection,event,post_data);
		else if(is_play_game!=""&&is_play_game!="false")
			play_game_handler(connection,event,post_data);
		else
			mg_serve_http(connection,message,*options);
	}
}
