#include "Levels.h"

int MarioLife=3;


void HoleColl(){
    for(int i=0; i<Holes.size(); i++){
        if (slidX>=Holes[i].x1-805 && slidX+50<=Holes[i].x2-795 && position_y==500){
            GameFlag=false;

        }
    }

}

void GoombaColl(){
    
    for(int i=0; i<Goombas.size(); i++){
        if (Goombas[i].Death == false){
            //if ((slidX>=Goombas[0].x1-850 && slidX<=Goombas[0].x1-800 || slidX>=Goombas[0].x2-825 && slidX<=Goombas[0].x2-800) && position_y==500){
            if ((slidX>=Goombas[i].x1-850 && slidX<=Goombas[i].x1-800 || slidX>(Goombas[i].x2)-850 && slidX<=(Goombas[i].x2)-800) && (position_y+50>=Goombas[i].y1+17 && position_y+50<=Goombas[i].y2)){// fix y below the goomba (position_y-5>=Goombas[i].y1 && position_y+2<=Goombas[i].y2 || position_y+43>=Goombas[i].y1 && position_y+52<=Goombas[i].y2)){ //detects running into goomba
                GameFlag=false;

            }
            else if(velocity_y>=0 && (slidX>=Goombas[i].x1-850 && slidX<=Goombas[i].x1-800 || slidX>(Goombas[i].x2)-850 && slidX<=(Goombas[i].x2)-800) && (position_y+50>=Goombas[i].y1-10 && position_y+50<=Goombas[i].y1+10)){ // to detect jumping on goomba
                Goombas[i].Death = true;
                velocity_y = -8.5;
                if (Goombas[i].PointChecked==false){
                    Point+=200;
                    Goombas[i].PointChecked=true;
                }
            }

        }
    
    }

}

void KoopaColl(){
    
    for(int i=0; i<Koopas.size(); i++){
        if (Koopas[i].Death == false){
            if ((slidX>=Koopas[i].x1-850 && slidX<=Koopas[i].x1-800 || slidX>(Koopas[i].x2)-850 && slidX<=(Koopas[i].x2)-800) && (position_y+50>=Koopas[i].y1+17 && position_y+50<=Koopas[i].y2)){// fix y below the goomba (position_y-5>=Goombas[i].y1 && position_y+2<=Goombas[i].y2 || position_y+43>=Goombas[i].y1 && position_y+52<=Goombas[i].y2)){ //detects running into goomba
                GameFlag=false;

            }
            else if(Koopas[i].State==1 && velocity_y>=0 && (slidX>=Koopas[i].x1-850 && slidX<=Koopas[i].x1-800 || slidX>(Koopas[i].x2)-850 && slidX<=(Koopas[i].x2)-800) && (position_y+50>=Koopas[i].y1-10 && position_y+50<=Koopas[i].y1+10)){ // to detect jumping on goomba
                Koopas[i].State = 2;            
                velocity_y = -8.5;

            }
            else if(Koopas[i].State==2 && velocity_y>=0 && (slidX>=Koopas[i].x1-850 && slidX<=Koopas[i].x1-800 || slidX>(Koopas[i].x2)-850 && slidX<=(Koopas[i].x2)-800) && (position_y+50>=Koopas[i].y1-10 && position_y+50<=Koopas[i].y1+10)){ // to detect jumping on goomba
                Koopas[i].Death = true;
                velocity_y = -8.5;
                if (Koopas[i].PointChecked==false){
                    Point+=300;
                    Koopas[i].PointChecked=true;
                }
            }

        }
    
    }

}

    void run() {
    // Create the start screen window


    //main game (before removing while loops)
        
        
//slidX=6200; //REMOVE

    // Run the program as long as the window is open
    while (window.isOpen()){

        if(GameCurrentState == 0){

        // START SCREEN
            
        sf::Texture texture;
        if(!texture.loadFromFile("/home/sumit/Sumit/Project/StartScreen.png")); ///home/sumit/Sumit/Project/mario.png
        sf::Sprite sprite(texture);
        //sprite.setPosition(x, y);
        window.draw(sprite);


        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(30);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color(241,146,189));
        text.setString("Press Enter to Start");
        text.setPosition(200,350);

        int W=800; int H=600;


        sf::Image skyImage;
        skyImage.create(W, H, sf::Color::Black);

        for(int y=0; y<H; y++){
            for(int x=0; x<W; x++){
                skyImage.setPixel(x, y, sf::Color(0, 0, 0)); 
            }
        }


        window.draw(text);

        window.display();
        window.setFramerateLimit(60); //NEEDED TO ENSURE GAME RUNS AT RIGHT SPEED
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){ 
                GameCurrentState=1; 
                dClock.restart();
            }
        }

        // PHYSICAL GAME
        if(GameCurrentState == 1){
            if (DrawLevel==true){
                Level1();
                DrawLevel=false;
            }
            
            if (GameFlag)
            {
            

                float seconds = dClock.getElapsedTime().asSeconds();; 

                std::ostringstream ss;
                ss << std::fixed << std::setprecision(2) << seconds;  


        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(20);
        text.setStyle(sf::Text::Regular);
        text.setFillColor(sf::Color(200,0,0));
        text.setString(ss.str());
        text.setPosition(700,30);

        sf::Text text2;
        text2.setFont(font);
        text2.setCharacterSize(20);
        text2.setStyle(sf::Text::Regular);
        text2.setFillColor(sf::Color(200,0,0));
        text2.setString("Time");
        text2.setPosition(700,10);

        sf::Text text3;
        text3.setFont(font);
        text3.setCharacterSize(20);
        text3.setStyle(sf::Text::Regular);
        text3.setFillColor(sf::Color(200,0,0));
        text3.setString(std::to_string(Point));
        text3.setPosition(40,30);

        sf::Text text4;
        text4.setFont(font);
        text4.setCharacterSize(20);
        text4.setStyle(sf::Text::Regular);
        text4.setFillColor(sf::Color(200,0,0));
        text4.setString("Points");
        text4.setPosition(40,10);

        sf::Text text5;
        text5.setFont(font);
        text5.setCharacterSize(20);
        text5.setStyle(sf::Text::Regular);
        text5.setFillColor(sf::Color(200,0,0));
        text5.setString(std::to_string(Coin));
        text5.setPosition(250,30);

        sf::Text text6;
        text6.setFont(font);
        text6.setCharacterSize(20);
        text6.setStyle(sf::Text::Regular);
        text6.setFillColor(sf::Color(200,0,0));
        text6.setString("Coins");
        text6.setPosition(250,10);

        sf::Text text7;
        text7.setFont(font);
        text7.setCharacterSize(20);
        text7.setStyle(sf::Text::Regular);
        text7.setFillColor(sf::Color(200,0,0));
        text7.setString(std::to_string(Level));
        text7.setPosition(500,30);

        sf::Text text8;
        text8.setFont(font);
        text8.setCharacterSize(20);
        text8.setStyle(sf::Text::Regular);
        text8.setFillColor(sf::Color(200,0,0));
        text8.setString("Level");
        text8.setPosition(500,10);

        GoombaMov();
        GravityCheck();
        GroundColl();
        PipeColl();
        BlockColl();
        GoombaColl();
        HoleColl();
        UpdateFlags();


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            slidX-=6; sliderX-=6;      
            PipeColl();
            BlockColl();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){ 
            slidX+=6; sliderX+=6;
            PipeColl();
            BlockColl();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && (OnGround || ObjectCollision)){ 
            velocity_y=-12.5f; 
            OnGround=false;
            ObjectCollision=false;
        }

            velocity_y+=gravity;
            position_y+=velocity_y; 
            //std::cout<< position_y << "\n";


        if (sliderX+700>800){  //sky layer movement
            sliderX=sliderX-5;
        }
        else if (sliderX<0){
            sliderX=sliderX+5;
        }

        if (slidX<-560){
        
            slidX=-560;
        }



        if (slidX>6750) //flag pole to lvl 2
        {
            NextLevel();
            GameCurrentState=3;
        }
         
        // Clear the window with red color
        window.clear(sf::Color::Red);
        

        ShowBackGround(); 
        ShowGround(); 
        DrawClouds();
        DrawCastles();

        window.draw(text);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        window.draw(text5);
        window.draw(text6);        
        window.draw(text7);
        window.draw(text8);   

        DrawBlocks();
        DrawGoomba();
        DrawFlags();

        Character(position_x, position_y); 


        // Display whatever has been drawn to the window
        window.display();
        }
        else{

            if (GameFlag==false)
            {

                MarioLife-=1;
                GameCurrentState=2; // FINAL DEATH SCREEN (ADD ONE FOR -1 LIFE)
            }
            else
            {
                NextLevel();
                Level+=1;
                DrawLevel=true;
                GameCurrentState=3; // LEVEL 2

            }
            
        }
    }

    if (GameCurrentState==3) // LEVEL 2
    {

            if (DrawLevel==true){
                Level2();
                DrawLevel=false;
            }

            if (Flags[0].PointChecked==true){
                Flags[0].PointChecked=false;
            }            
            
            if (GameFlag)
            {
            

                float seconds = dClock.getElapsedTime().asSeconds();; 

                std::ostringstream ss;
                ss << std::fixed << std::setprecision(2) << seconds;  


        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(20);
        text.setStyle(sf::Text::Regular);
        text.setFillColor(sf::Color(200,0,0));
        text.setString(ss.str());
        text.setPosition(700,30);

        sf::Text text2;
        text2.setFont(font);
        text2.setCharacterSize(20);
        text2.setStyle(sf::Text::Regular);
        text2.setFillColor(sf::Color(200,0,0));
        text2.setString("Time");
        text2.setPosition(700,10);

        sf::Text text3;
        text3.setFont(font);
        text3.setCharacterSize(20);
        text3.setStyle(sf::Text::Regular);
        text3.setFillColor(sf::Color(200,0,0));
        text3.setString(std::to_string(Point));
        text3.setPosition(40,30);

        sf::Text text4;
        text4.setFont(font);
        text4.setCharacterSize(20);
        text4.setStyle(sf::Text::Regular);
        text4.setFillColor(sf::Color(200,0,0));
        text4.setString("Points");
        text4.setPosition(40,10);

        sf::Text text5;
        text5.setFont(font);
        text5.setCharacterSize(20);
        text5.setStyle(sf::Text::Regular);
        text5.setFillColor(sf::Color(200,0,0));
        text5.setString(std::to_string(Coin));
        text5.setPosition(250,30);

        sf::Text text6;
        text6.setFont(font);
        text6.setCharacterSize(20);
        text6.setStyle(sf::Text::Regular);
        text6.setFillColor(sf::Color(200,0,0));
        text6.setString("Coins");
        text6.setPosition(250,10);

        sf::Text text7;
        text7.setFont(font);
        text7.setCharacterSize(20);
        text7.setStyle(sf::Text::Regular);
        text7.setFillColor(sf::Color(200,0,0));
        text7.setString(std::to_string(Level));
        text7.setPosition(500,30);

        sf::Text text8;
        text8.setFont(font);
        text8.setCharacterSize(20);
        text8.setStyle(sf::Text::Regular);
        text8.setFillColor(sf::Color(200,0,0));
        text8.setString("Level");
        text8.setPosition(500,10);

        GoombaMov();
        KoopaMov();
        GravityCheck();
        GroundColl();
        PipeColl();
        BlockColl();
        GoombaColl();
        KoopaColl();
        HoleColl();
        UpdateFlags();
        

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            slidX-=6; sliderX-=6;      
            PipeColl();
            BlockColl();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){ 
            slidX+=6; sliderX+=6;
            PipeColl();
            BlockColl();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && (OnGround || ObjectCollision)){ 
            velocity_y=-12.5f; 
            OnGround=false;
            ObjectCollision=false;
        }

            velocity_y+=gravity;
            position_y+=velocity_y; 
            //std::cout<< position_y << "\n";


        if (sliderX+700>800){  //sky layer movement
            sliderX=sliderX-5;
        }
        else if (sliderX<0){
            sliderX=sliderX+5;
        }

        if (slidX<-560){
        
            slidX=-560;
        }


        if (slidX>6750) //flag pole to lvl 3
        {
            NextLevel();
            GameCurrentState=4;
        }
         
        // Clear the window with red color
        window.clear(sf::Color::Red);
        

        ShowBackGround(); 
        ShowGround(); 
        DrawClouds();
        DrawCastles();

        window.draw(text);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        window.draw(text5);
        window.draw(text6);        
        window.draw(text7);
        window.draw(text8);   

        DrawBlocks();
        DrawGoomba();
        DrawKoopa();
        DrawFlags();

        Character(position_x, position_y); 


        // Display whatever has been drawn to the window
        window.display();
        }
        else{

            if (GameFlag==false)
            {
                MarioLife-=1;
                GameCurrentState=2; 
            }
            else
            {
                Level+=1;
                DrawLevel=true;
                GameCurrentState=4; // LEVEL 3
            }
            
        }

    }

        if (GameCurrentState==2){ //-1 LIFE SCREEN

            sf::Texture texture;
            if(!texture.loadFromFile("/home/sumit/Sumit/Project/death1.png")); 
            sf::Sprite sprite(texture);
            window.draw(sprite);
        


        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(35);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color(220,220,220));
        text.setString(std::to_string(MarioLife));
        text.setPosition(420,270);

        sf::Text text2;
        text2.setFont(font);
        text2.setCharacterSize(35);
        text2.setStyle(sf::Text::Bold);
        text2.setFillColor(sf::Color(220,220,220));
        text2.setString(std::to_string(Level));
        text2.setPosition(425,180);

        sf::Text text3;
        text3.setFont(font);
        text3.setCharacterSize(30);
        text3.setStyle(sf::Text::Bold);
        text3.setFillColor(sf::Color(220,220,220));
        text3.setString("Press R to Restart");
        text3.setPosition(200,380);

        int W=800; int H=600;



        sf::Image skyImage;
        skyImage.create(W, H, sf::Color::Black);

        for(int y=0; y<H; y++){
            for(int x=0; x<W; x++){
                skyImage.setPixel(x, y, sf::Color(0, 0, 0)); 
            }
        }


        window.draw(text);
        window.draw(text2);
        window.draw(text3);

        window.display();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){ 
                GameFlag=true;
                slidX=0; //position_y=500; 
                if (Level==1)
                {
                    position_y=500;
                    GameCurrentState=1; 
                }
                else if(Level==2){
                    //slidX=6000;
                    position_y=500;
                    GameCurrentState=3; 
                }
                else if(Level==3){
                    position_y=300;
                    GameCurrentState=4; 
                }                

            }
            

            if(MarioLife==0){
                GameCurrentState=8;
            }
        }

    if (GameCurrentState==4){ //FINAL WIN SCREEN 
            
        sf::Texture Wintexture;
        if(!Wintexture.loadFromFile("/home/sumit/Sumit/Project/WinScreen.jpg")); 
        sf::Sprite sprite(Wintexture);

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(20);
        text.setStyle(sf::Text::Regular);
        text.setFillColor(sf::Color(200,0,0));
        text.setString(std::to_string(MarioLife));
        text.setPosition(700,30);

        sf::Text text2;
        text2.setFont(font);
        text2.setCharacterSize(20);
        text2.setStyle(sf::Text::Regular);
        text2.setFillColor(sf::Color(200,0,0));
        text2.setString("Lives");
        text2.setPosition(700,10);

        sf::Text text3;
        text3.setFont(font);
        text3.setCharacterSize(20);
        text3.setStyle(sf::Text::Regular);
        text3.setFillColor(sf::Color(200,0,0));
        text3.setString(std::to_string(Point));
        text3.setPosition(40,30);

        sf::Text text4;
        text4.setFont(font);
        text4.setCharacterSize(20);
        text4.setStyle(sf::Text::Regular);
        text4.setFillColor(sf::Color(200,0,0));
        text4.setString("Points");
        text4.setPosition(40,10);

        sf::Text text5;
        text5.setFont(font);
        text5.setCharacterSize(20);
        text5.setStyle(sf::Text::Regular);
        text5.setFillColor(sf::Color(200,0,0));
        text5.setString(std::to_string(Coin));
        text5.setPosition(250,30);

        sf::Text text6;
        text6.setFont(font);
        text6.setCharacterSize(20);
        text6.setStyle(sf::Text::Regular);
        text6.setFillColor(sf::Color(200,0,0));
        text6.setString("Coins");
        text6.setPosition(250,10);

        sf::Text text7;
        text7.setFont(font);
        text7.setCharacterSize(20);
        text7.setStyle(sf::Text::Regular);
        text7.setFillColor(sf::Color(200,0,0));
        text7.setString(std::to_string(Level));
        text7.setPosition(500,30);

        sf::Text text8;
        text8.setFont(font);
        text8.setCharacterSize(20);
        text8.setStyle(sf::Text::Regular);
        text8.setFillColor(sf::Color(200,0,0));
        text8.setString("Level");
        text8.setPosition(500,10);

        sf::Text text9;
        text9.setFont(font);
        text9.setCharacterSize(30);
        text9.setStyle(sf::Text::Bold);
        text9.setFillColor(sf::Color(240,240,240));
        text9.setString("Press Escape to Exit");
        text9.setPosition(200,350);

        int W=800; int H=600;


        sf::Image skyImage;
        skyImage.create(W, H, sf::Color::Black);

        for(int y=0; y<H; y++){
            for(int x=0; x<W; x++){
                skyImage.setPixel(x, y, sf::Color(0, 0, 0)); 
            }
        }

        window.draw(sprite);
        window.draw(text);
        window.draw(text2);
        window.draw(text3);
        window.draw(text4);
        window.draw(text5);
        window.draw(text6);
        window.draw(text7);
        window.draw(text8);
        window.draw(text9);

        window.display();
        }

    if (GameCurrentState==8){ //FINAL DEATH SCREEN

            sf::Texture texture;
            if(!texture.loadFromFile("/home/sumit/Sumit/Project/gameover.png")); 
            sf::Sprite sprite(texture);
            window.draw(sprite);
        
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(30);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color(250,250,250));
        text.setString("Press Escape to Exit");
        text.setPosition(200,250);

        int W=800; int H=600;



        sf::Image skyImage;
        skyImage.create(W, H, sf::Color::Black);

        for(int y=0; y<H; y++){
            for(int x=0; x<W; x++){
                skyImage.setPixel(x, y, sf::Color(0, 0, 0)); 
            }
        }


        window.draw(text);

        window.display();


        }

        // Check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
            }
            
        }

    }
    
}