//
//  tttGame.h
//  first
//
//  Created by BOB on 1/20/16.
//  Copyright (c) 2016 Heartbreak Gorillas. All rights reserved.
//

#ifndef first_tttGame_h
#define first_tttGame_h

class button{
public:
    button():o(false){
        b=sf::RectangleShape(sf::Vector2f(0,0));
        b.setOrigin(0, 0);
        b.setFillColor(sf::Color::Red);
    };
    
    button(sf::Vector2f s, float oX, float oY):o(false){
        b=sf::RectangleShape(sf::Vector2f(s.x,s.y));
        b.setPosition(oX, oY);
        b.setFillColor(sf::Color::Red);
        o = true;
    };
    
    button(sf::RectangleShape r)
    {
        b=r;
    };
    
    sf::RectangleShape getRect(){
        return b;
    }
    
    void setButton(sf::Vector2f s, float oX, float oY){
        b=sf::RectangleShape(sf::Vector2f(s.x,s.y));
        b.setPosition(oX, oY);
        b.setOrigin(sf::Vector2f(oX,oY));
    }
    
    void click(sf::Vector2i mouse)
    {
        if(mouse.x>b.getPosition().x&&mouse.x<b.getPosition().x+b.getSize().x&&
           mouse.y>b.getPosition().y&&mouse.y<b.getPosition().y+b.getSize().y)
        {
            if(o)
            {
                b.setFillColor(sf::Color::Blue);
                o=!o;
            }else{
                b.setFillColor(sf::Color::Transparent);
                o=!o;
            }
        }
        
    }
    
    sf::RectangleShape display()
    {
        return b;
    }
    
private:
    sf::RectangleShape b;
    bool o;
    
};

class checker {
public:
    checker(){
        b=sf::CircleShape(12,12);
        b.setOrigin(0, 0);
        b.setFillColor(sf::Color::Red);
        b.setOutlineColor(sf::Color::White);
        b.setOutlineThickness(2);
        
    };
    
    checker(float oX, float oY, sf::Color c, sf::Color c2, float r=30){
        b=sf::CircleShape(r);
        b.setPosition(oX+r/2, oY);
        b.setFillColor(c);
        b.setOutlineColor(c2 );
        b.setOutlineThickness(2);
    };
    
    checker(sf::CircleShape r)
    {
        b=r;
    };
    
    sf::CircleShape display()
    {
        return b;
    }
    
private:
    sf::CircleShape b;
    
};

//Remake with squares that also make buttons? easier to make into checkers? DAY LIGHT
class tttGameBoard{
public:
    tttGameBoard():origin(0,0),wihi(50,50)
    {
        //makeBoard1();
        makeBoard2();
    }
    tttGameBoard(float w, float h, float oX, float oY, int s):origin(oX,oY),wihi(w,h)
    {
        //makeBoard1();
        makeBoard2(s,s);
        //makeBoard3(8,8);
    }
    
    void makeBoard1(){
        
        sf::RectangleShape temp;
        
        temp.setSize(sf::Vector2f(2*(wihi.x/50),wihi.y));
        temp.setPosition(wihi.x/3-2*(wihi.x/50), 0);
        lines.push_back(temp);
        
        temp.setPosition((wihi.x/3)*2, 0);
        lines.push_back(temp);
        
        temp.setSize(sf::Vector2f(wihi.x,2*(wihi.x/50)));
        temp.setPosition(0, wihi.y/3-2*(wihi.x/50));
        lines.push_back(temp);
        
        temp.setPosition(0, (wihi.y/3)*2);
        lines.push_back(temp);
        
    }
    
    void makeBoard2(){
        
        sf::RectangleShape temp;
        
        temp.setSize(sf::Vector2f(wihi.x/3,wihi.y/3));
        
        temp.setFillColor(sf::Color::Transparent);
        temp.setOutlineColor(sf::Color::Green);
        temp.setOutlineThickness(2);
        
        //top
        temp.setPosition(origin.x+wihi.x/3+temp.getOutlineThickness(),origin.y);
        lines.push_back(temp);
        
        //left
        temp.setPosition(origin.x,origin.y+wihi.y/3+temp.getOutlineThickness());
        lines.push_back(temp);
        
        //right
        temp.setPosition((origin.x+wihi.x/3+temp.getOutlineThickness())*2,origin.y+wihi.y/3+temp.getOutlineThickness());
        lines.push_back(temp);
        
        //bottom
        temp.setPosition((origin.x+wihi.x/3+temp.getOutlineThickness()),(origin.y+wihi.y/3+temp.getOutlineThickness())*2);
        lines.push_back(temp);
        
        
    }
    
    void makeBoard2(int spacesX, int spacesY){
        
        sf::RectangleShape temp;
        sf::RectangleShape temp2;
        
        temp.setOutlineThickness(2);
        temp2.setFillColor(sf::Color::Transparent);
        temp2.setSize(sf::Vector2f((wihi.x-(temp.getOutlineThickness()*2))/spacesX,(wihi.y-(temp.getOutlineThickness()*2))/spacesY));
        
        temp.setSize(sf::Vector2f((wihi.x-(temp.getOutlineThickness()*2))/spacesX,(wihi.y-(temp.getOutlineThickness()*2))/spacesY));
        temp.setFillColor(sf::Color::Red);
        temp.setOutlineColor(sf::Color::Green);
        temp.setOutlineThickness(2);
        
        for(int jj=0; jj<spacesX; jj++)
        {
            for(int ii=0;ii<spacesY; ii++)
            {
                if(!(ii%2))
                {
                    if(jj%2)
                    {
                        temp.setPosition(origin.x+((wihi.x/spacesX+temp.getOutlineThickness()))*(ii),origin.y+(wihi.y/spacesY+temp.getOutlineThickness())*(jj));
                        lines.push_back(temp);
                    }
                }
                else{
                    if(!(jj%2))
                    {
                        temp.setPosition(origin.x+((wihi.x/spacesX+temp.getOutlineThickness()))*(ii),origin.y+(wihi.y/spacesY+temp.getOutlineThickness())*(jj));
                        lines.push_back(temp);
                    }
                }
                
                temp2.setPosition(origin.x+((wihi.x/spacesX+temp.getOutlineThickness()))*(ii),origin.y+(wihi.y/spacesY+temp.getOutlineThickness())*(jj));
                butts.push_back(temp2);
            }
        }
    }
    
    void click(sf::Vector2i mouse)
    {
        for(int ii=0;ii<butts.size(); ii++)
        {
            butts[ii].click(mouse);
        }
    }
    
    std::vector<sf::RectangleShape> dispalyBoard()
    {
        return lines;
    }
    
    std::vector<button> displayButtons()
    {
        return butts;
    }
    
private:
    sf::Vector2f origin;
    sf::Vector2f wihi;
    std::vector<sf::RectangleShape> lines;
    std::vector<button> butts;
    
};

class tttGame{
public:
    tttGame():origin(0,0),wihi(50,50)
    {}
    
    tttGame(float w, float h,int s, float oX=0, float oY=0):origin(oX,oY),wihi(w,h)
    {
        board=tttGameBoard(wihi.x,wihi.y,origin.x,origin.y,s);
    }
    
    std::vector<sf::RectangleShape> displayBoard()
    {
        return board.dispalyBoard();
    }
    
    void displayBoard2(sf::RenderWindow & win)
    {
        
        for(int ii=0; ii<board.dispalyBoard().size(); ii++)
        {
            win.draw(board.dispalyBoard()[ii]);
        }
        
        for(int ii=0; ii<board.displayButtons().size(); ii++)
        {
            win.draw(board.displayButtons()[ii].display());
        }
        
        for(int ii=0; ii<checkers.size(); ii++)
        {
            win.draw(checkers[ii].display());
        }
    }
    
    void readIn (std::vector<char> cs)
    {
        sf::Color c;
        sf::Color c2;
        sf::Vector2f pos = displayBoard()[0].getPosition();
        for(int ii=0; ii<cs.size(); ii++)
        {
            if(cs[ii]=='r'||cs[ii]=='R')
            {
                c = sf::Color::Red;
                c2 = sf::Color::White;
                
            }
            else if(cs[ii]=='b'||cs[ii]=='B')
            {
                c = sf::Color::Black;
                c2 = sf::Color::White;
                if(cs[ii]=='B')
                {
                    
                }
            }
            else{
                c = sf::Color::Transparent;
                c2 = sf::Color::Transparent;
            }
            
            pos = displayBoard()[ii].getPosition();
            
            checkers.push_back(checker(pos.x, pos.y, c,c2,5));
            
        }
        
        //checkers.push_back(checker(pos.x, pos.y, c,c2));
    }
    
    void click(sf::Vector2i mouse)
    {
        board.click(mouse);
    }
    
private:
    sf::Vector2f origin;
    sf::Vector2f wihi;
    tttGameBoard board;
    std::vector<checker> checkers;
    
    
};

#endif
