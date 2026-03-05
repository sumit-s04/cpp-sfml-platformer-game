#include <SFML/Graphics.hpp>
#include <SFML/System.hpp> 
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>


const std::string dir_font = "/home/sumit/Sumit/Project/SuperMario256.ttf"; 
sf::Font font;

sf::Texture blockTexture;
sf::Texture marioTexture;
sf::Texture coinTexture;
sf::Texture brokenBlockTex;
sf::Texture goombaTexture;
sf::Texture cloudTexture;
sf::Texture koopaTexture;
sf::Texture shellTexture;
sf::Texture castleTexture;
sf::Texture flagTexture;


//struct Mario{
    int position_x=400; //layer 2
    int position_y=500; int y2=position_y+50;
    float velocity_y=0;
    float gravity=0.6f;
//};

int slidX = 0; 
int sliderX = 0; int sliderY = 0; //layer 1

int sky[700][1600]; //[y][x]

int Dirt[700][800*10]; //[y][x]

sf::RenderWindow window(sf::VideoMode(800, 600), "Super Mario Bros.");
sf::Clock dClock;

struct ObjectParam{
    int x1; 
    int y1; 
    int x2; 
    int y2; 
    bool PointChecked = false;
    bool Special = false;
    sf::Sprite sprite;

}; 

struct NPCParam{
    int x1; 
    int y1; 
    int x2; 
    int y2; 
    int startP;
    int endP;
    bool DirRight = true;
    bool Death = false;
    int State = 1;
    bool PointChecked = false;
    sf::Sprite sprite;

}; 


std::vector<ObjectParam>Blocks;
std::vector<ObjectParam>Pipes;
std::vector<ObjectParam>Lands;
std::vector<ObjectParam>Holes;
std::vector<ObjectParam>Clouds;
std::vector<ObjectParam>Castles;
std::vector<ObjectParam>Flags;


std::vector<NPCParam>Goombas;
std::vector<NPCParam>Koopas;


uint8_t GameCurrentState = 0; 



bool GameFlag=true;
bool OnGround = true;
bool ObjectCollision = false; //is this needed?
bool DrawLevel=true;


int Point=0; 
int Level=1;
int Coin=0;




void Lvl1Textures()
{
    
    if(!blockTexture.loadFromFile("/home/sumit/Sumit/Project/br(1).jpg"));

    if(!marioTexture.loadFromFile("/home/sumit/Sumit/Project/mario.png")); 
        
    if(!coinTexture.loadFromFile("/home/sumit/Sumit/Project/cb(1).png")); 

    if(!brokenBlockTex.loadFromFile("/home/sumit/Sumit/Project/brokenBlock.png")); 

    if(!goombaTexture.loadFromFile("/home/sumit/Sumit/Project/goomba.png")); 

    if(!cloudTexture.loadFromFile("/home/sumit/Sumit/Project/cl(1).png")); 

    if(!castleTexture.loadFromFile("/home/sumit/Sumit/Project/castl(1).png")); 

    if(!flagTexture.loadFromFile("/home/sumit/Sumit/Project/Flag.png")); 

}

void Lvl2Textures()
{
    
    if(!blockTexture.loadFromFile("/home/sumit/Sumit/Project/blu(1).jpg"));

    if(!marioTexture.loadFromFile("/home/sumit/Sumit/Project/mario.png")); 
        
    if(!coinTexture.loadFromFile("/home/sumit/Sumit/Project/cb(1).png")); 

    if(!brokenBlockTex.loadFromFile("/home/sumit/Sumit/Project/brokenBlock.png")); //MAYBE CHANGE

    if(!goombaTexture.loadFromFile("/home/sumit/Sumit/Project/goomb.png")); 

    if(!cloudTexture.loadFromFile("/home/sumit/Sumit/Project/c2(1).png")); 

    if(!koopaTexture.loadFromFile("/home/sumit/Sumit/Project/koopa.png")); 
    if(!shellTexture.loadFromFile("/home/sumit/Sumit/Project/shell.png")); 
    //add koopa changing sides?

    if(!castleTexture.loadFromFile("/home/sumit/Sumit/Project/castle(1).png")); 

    if(!flagTexture.loadFromFile("/home/sumit/Sumit/Project/Flag.png")); 

}



void ShowBackGround(){ //shows the sky (layer 1) 
    sf::Image SkyView;
    SkyView.create(800, 600, sf::Color::Black);

    for(int y=0; y<600; y++){
        for(int x=0; x<800; x++){
            SkyView.setPixel(x, y, (sf::Color)sky[y+sliderY+100][x+sliderX+400]);//sf::Color(x+50, y+50, x+y+100)

        }
    }

    sf::Texture SkyViewTex;
    SkyViewTex.loadFromImage(SkyView);
    sf::Sprite SkyViewSprite(SkyViewTex);
    window.draw(SkyViewSprite); 
}


void ShowGround(){ //shows game ground (layer 2) 
    sf::Image GroundView;
    GroundView.create(800, 600, sf::Color::Black);


    for(int y=0; y<600; y++){
        for(int x=0; x<800; x++){
            GroundView.setPixel(x, y, (sf::Color)Dirt[y][x+slidX+400]);//sf::Color(x+50, y+50, x+y+100)
        }
    }

    sf::Texture GroundViewTex;
    GroundViewTex.loadFromImage(GroundView);
    sf::Sprite GroundViewSprite(GroundViewTex);
    window.draw(GroundViewSprite); 
}


void Character(int x, int y){
    /*sf::Image image;
    image.create(50, 50, sf::Color::Black);
    for(int y=0; y<50; y++){
        for(int x=0; x<50; x++){
            image.setPixel(x, y, sf::Color(150,0,0));

        }
    }*/

    sf::Sprite sprite(marioTexture);
    sprite.setPosition(x, y);
    window.draw(sprite);
}

//int initialX=0;
//int EndX=0;

void Goomba(int X, int Y, int EndX){
    
    
        NPCParam newNPC;
        newNPC.x1 = X; 
        newNPC.x2 = X+50; 
        newNPC.y1 = Y; 
        newNPC.y2 = Y+50; 
        newNPC.startP = X;
        newNPC.endP = EndX;
        newNPC.sprite.setTexture(goombaTexture);
        newNPC.sprite.setPosition(X, Y);
        Goombas.push_back(newNPC); 

}

void DrawGoomba(){ //PUT IN MAIN LOOP
        int camOffset = slidX + 400; 

        for(int i=0; i<Goombas.size(); i++){
            if(Goombas[i].Death == false){
                float screenX = Goombas[i].x1 - camOffset;
                float screenY = Goombas[i].y1;

                Goombas[i].sprite.setPosition(screenX, screenY);

                window.draw(Goombas[i].sprite);   
            }
        }     

}

void GoombaMov(){

        for(int i=0; i<Goombas.size(); i++){
            if(Goombas[i].Death == false){
                if (Goombas[i].x2>=Goombas[i].endP) 
                {
                    Goombas[i].DirRight = false;
                }
                else if(Goombas[i].x1<=Goombas[i].startP){
                    Goombas[i].DirRight = true;
                }

                if (Goombas[i].DirRight==true){
                    Goombas[i].x1+=3;
                    Goombas[i].x2+=3;
                }
                else if(Goombas[i].DirRight==false){
                    Goombas[i].x1-=3;
                    Goombas[i].x2-=3;
                }

            }
        }
}

void Koopa(int X, int Y, int EndX){
    
        NPCParam newNPC;
        newNPC.x1 = X; 
        newNPC.x2 = X+50; 
        newNPC.y1 = Y; 
        newNPC.y2 = Y+50; 
        newNPC.startP = X;
        newNPC.endP = EndX;
        newNPC.sprite.setTexture(koopaTexture);
        newNPC.sprite.setPosition(X, Y);
        Koopas.push_back(newNPC); 

}

void DrawKoopa(){ //PUT IN MAIN LOOP
        int camOffset = slidX + 400; 

        for(int i=0; i<Koopas.size(); i++){
            if(Koopas[i].Death == false){
                float screenX = Koopas[i].x1 - camOffset;
                float screenY = Koopas[i].y1;

                Koopas[i].sprite.setPosition(screenX, screenY);
                if (Koopas[i].State==2){
                    Koopas[i].sprite.setTexture(shellTexture);
                }

                window.draw(Koopas[i].sprite);   
            }
        }     

}

void KoopaMov(){

        for(int i=0; i<Koopas.size(); i++){
            if(Koopas[i].Death == false){
                if (Koopas[i].x2>=Koopas[i].endP) 
                {
                    Koopas[i].DirRight = false;
                }
                else if(Koopas[i].x1<=Koopas[i].startP){
                    Koopas[i].DirRight = true;
                }

                if(Koopas[i].State == 1){

                    if (Koopas[i].DirRight==true){
                        Koopas[i].x1+=4;
                        Koopas[i].x2+=4;
                    }
                    else if(Koopas[i].DirRight==false){
                        Koopas[i].x1-=4;
                        Koopas[i].x2-=4;
                    }
                }

                else if(Koopas[i].State == 2){
                    if (Koopas[i].DirRight==true){
                        Koopas[i].x1+=8;
                        Koopas[i].x2+=8;
                    }
                    else if(Koopas[i].DirRight==false){
                        Koopas[i].x1-=8;
                        Koopas[i].x2-=8;
                    }
                }
            }
        }
}



void CreateDirt(int X, int Y, int D){ //int D will be the distance of the plot of land
    for(int y=Y; y<600; y++){
        for(int x=X; x<X+D; x++){
            Dirt[y][x]=sf::Color(54,20,1).toInteger();             
        }
    }
ObjectParam newObject;
newObject.x1 = X; 
newObject.x2 = X+D; 
newObject.y1 = Y; 
newObject.y2 = 600; 
Lands.push_back(newObject); 
}

void Hole(int X, int Y){ //int D will be the distance of the plot of land
    for(int y=Y; y<600; y++){
        for(int x=X; x<X+70; x++){
            Dirt[y][x]=sf::Color(0, 0, 0, 0).toInteger();             
        }
    }
ObjectParam newObject;
newObject.x1 = X; 
newObject.x2 = X+70; 
newObject.y1 = Y; 
newObject.y2 = 600; 
Holes.push_back(newObject); 
}

void Cloud(int X, int Y){ //make objParam

    ObjectParam newObject;
    newObject.x1 = X; 
    newObject.y1 = Y; 
    newObject.sprite.setTexture(cloudTexture);
    newObject.sprite.setPosition(X, Y);
    Clouds.push_back(newObject); 
}

void Flag(int X){
    for(int y=200; y<550; y++){
        for(int x=X; x<X+20; x++){
            Dirt[y][x] = sf::Color(200,176,26).toInteger();
        }
    }
    ObjectParam newObject;
    newObject.x1 = X; 
    newObject.x2 = X+20; 
    newObject.y1 = 200; 
    newObject.y2 = 550; 

    newObject.sprite.setTexture(flagTexture);
    newObject.sprite.setPosition(X+20, 200);
    Flags.push_back(newObject); 
}

void Castle(int X, int Y){ //make objParam

        ObjectParam newObject;
        newObject.x1 = X; 
        newObject.y1 = Y; 
        newObject.sprite.setTexture(castleTexture);
        newObject.sprite.setPosition(X, Y);
        Castles.push_back(newObject); 

}

void DrawFlags(){ // ONLY DRAWS THE FLAG BANNER NOT POLE
        int camOffset = slidX + 400; 

        for(int i=0; i<Flags.size(); i++){
                float screenX = Flags[i].x1 - camOffset + 20;
                float screenY = Flags[i].y1;

                Flags[i].sprite.setPosition(screenX, screenY);


                window.draw(Flags[i].sprite);   
        }
        
}

void DrawClouds(){
        int camOffset = slidX + 400; 

        for(int i=0; i<Clouds.size(); i++){
                float screenX = Clouds[i].x1 - camOffset;
                float screenY = Clouds[i].y1;

                Clouds[i].sprite.setPosition(screenX, screenY);

                window.draw(Clouds[i].sprite);   
        }
}

void DrawCastles(){
        int camOffset = slidX + 400; 

        for(int i=0; i<Castles.size(); i++){
                float screenX = Castles[i].x1 - camOffset;
                float screenY = Castles[i].y1;

                Castles[i].sprite.setPosition(screenX, screenY);

                window.draw(Castles[i].sprite);   
        }
}

void Pipe(int X){
        for(int y=470; y<480; y++){ //top part
            for(int x=X; x<70+X; x++){
                Dirt[y][x]=sf::Color(44, 176, 26).toInteger(); 
            }
        }        
               
        for(int y=470; y<570; y++){ //tube part
            for(int x=X+10; x<60+X; x++){
                Dirt[y][x]=sf::Color(44, 176, 26).toInteger(); 
            }
        }       

        for(int y=480; y<482; y++){ //top part
            for(int x=X; x<70+X; x++){
                Dirt[y][x]=sf::Color(5, 5, 5).toInteger(); 
            }
        }         
ObjectParam newObject;
newObject.x1 = X; 
newObject.x2 = X+70; 
newObject.y1 = 470; 
newObject.y2 = 570; 
Pipes.push_back(newObject); 
}
    

void Block(int Y, int b, bool Coin){

    if (Coin == true){
        ObjectParam newObject;
        newObject.x1 = b; 
        newObject.x2 = b+50; 
        newObject.y1 = Y; 
        newObject.y2 = Y+50; 
        newObject.Special = Coin;
        newObject.sprite.setTexture(coinTexture);
        newObject.sprite.setPosition(b, Y);
        Blocks.push_back(newObject); 
    }

    else {
        ObjectParam newObject;
        newObject.x1 = b; 
        newObject.x2 = b+50; 
        newObject.y1 = Y; 
        newObject.y2 = Y+50; 
        newObject.Special = Coin;
        newObject.sprite.setTexture(blockTexture);
        newObject.sprite.setPosition(b, Y);
        Blocks.push_back(newObject); 
    }

}

void DrawBlocks()
{
    // camera offset used in Dirt drawing
    int camOffset = slidX + 400; 

    for(int i=0; i<Blocks.size(); i++){
        float screenX = Blocks[i].x1 - camOffset;
        float screenY = Blocks[i].y1;

        Blocks[i].sprite.setPosition(screenX, screenY);

        window.draw(Blocks[i].sprite);
    }
}


void BlockColl(){
    for(int i=0; i<Blocks.size(); i++){
        if(slidX>=Blocks[i].x1-850 && slidX<=Blocks[i].x1-800 && (position_y>=Blocks[i].y1 && position_y+5<Blocks[i].y2 || position_y+43>Blocks[i].y1 && position_y+50<=Blocks[i].y2)){
            //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){ //might remove
                slidX=Blocks[i].x1-850;
                Character(position_x,position_y);
        }

        else if(slidX>=Blocks[i].x2-845 && slidX<=Blocks[i].x2-800 && (position_y>=Blocks[i].y1 && position_y+5<Blocks[i].y2 || position_y+43>Blocks[i].y1 && position_y+50<=Blocks[i].y2)){ //-5 X Gap on inside of block between left & right collisions, shouldn't matter outsides are all fine.
            //if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){ //might remove
                slidX=Blocks[i].x2-800;
                Character(position_x,position_y);
        }


        else if(velocity_y<=0 && (slidX>Blocks[i].x1-800 && slidX<Blocks[i].x2-800 || slidX+50>Blocks[i].x1-800 && slidX+50<Blocks[i].x2-800) && position_y>=Blocks[i].y2-5 && position_y<=Blocks[i].y2+5){ //need special case for last two when mario is perf under block? 


            if(Blocks[i].Special == false){
                velocity_y=1;
                Character(position_x,position_y);
                Blocks[i].sprite.setTexture(brokenBlockTex);

                if (Blocks[i].PointChecked==false){
                    Point+=50;
                    Blocks[i].PointChecked=true;
                }

            }

            else if(Blocks[i].Special==true){ //FOR COIN BLOCKS
                velocity_y=1;
                Character(position_x,position_y);
                Blocks[i].sprite.setTexture(brokenBlockTex);



                if (Blocks[i].PointChecked==false){
                    Point+=100;
                    Coin+=1;
                    Blocks[i].PointChecked=true;

                    
                    /*if((slidX>=Blocks[i].x1-800 && slidX<=Blocks[i].x2-800 || slidX+50>=Blocks[i].x1-800 && slidX+50<=Blocks[i].x2-800) && position_y == Blocks[i].y1-50){
                        for(int y=Blocks[i].y1-50; y<Blocks[i].y1; y++){ //coin part
                            for(int x=Blocks[i].x1; x<Blocks[i].x2; x++){
                                Dirt[y][x]=sf::Color(0, 0, 0, 0).toInteger(); 
                            }
                        }
                    }*/
                }
            }
            
        }

        else if(velocity_y<=0 && (slidX==Blocks[i].x1-800 && slidX+50==Blocks[i].x2-800) && position_y>=Blocks[i].y2-5 && position_y<=Blocks[i].y2+5){ //Special case for mario standing exactly under a block
            if(Blocks[i].Special==false){
                velocity_y=1;
                Character(position_x,position_y);
                Blocks[i].sprite.setTexture(brokenBlockTex);

                if (Blocks[i].PointChecked==false){
                    Point+=50;
                    Blocks[i].PointChecked=true;
                }
            }

            else if(Blocks[i].Special==true){ //FOR COIN BLOCKS
                velocity_y=1;
                Character(position_x,position_y);
                Blocks[i].sprite.setTexture(brokenBlockTex);



                if (Blocks[i].PointChecked==false){
                    Point+=100;
                    Coin+=1;                    
                    Blocks[i].PointChecked=true;
                    /*if((slidX>=Blocks[i].x1-800 && slidX<=Blocks[i].x2-800 || slidX+50>=Blocks[i].x1-800 && slidX+50<=Blocks[i].x2-800) && position_y == Blocks[i].y1-50){
                        for(int y=Blocks[i].y1-50; y<Blocks[i].y1; y++){ //coin part
                            for(int x=Blocks[i].x1; x<Blocks[i].x2; x++){
                                Dirt[y][x]=sf::Color(0, 0, 0, 0).toInteger(); 
                            }
                        }
                    }*/
                }
            }
        }


        else if(velocity_y>=0 && (slidX>Blocks[i].x1-800 && slidX<Blocks[i].x2-800 || slidX+50>Blocks[i].x1-800 && slidX+50<Blocks[i].x2-800) && position_y+50>=Blocks[i].y1-7 && position_y+50<=Blocks[i].y1+7){
            ObjectCollision=true;
            position_y=Blocks[i].y1-50;
            gravity=0;
            velocity_y=0;
            Character(position_x,position_y);
        }

        else if(velocity_y>=0 && (slidX==Blocks[i].x1-800 && slidX+50==Blocks[i].x2-800) && position_y+50>=Blocks[i].y1-7 && position_y+50<=Blocks[i].y1+7){  //special case mario directly over block
            ObjectCollision=true;
            position_y=Blocks[i].y1-50;
            gravity=0;
            velocity_y=0;
            Character(position_x,position_y);
        }
    }
}

void PipeColl(){ 
    for(int i=0; i<Pipes.size(); i++){
        if (slidX>=Pipes[i].x1-835 && slidX<=Pipes[i].x1-790 && position_y>Pipes[i].y1-41){ //left side
            slidX=Pipes[i].x1-840;
            Character(position_x,position_y);
        }

        else if (slidX>=Pipes[i].x2-865 && slidX<=Pipes[i].x2-810 && position_y>Pipes[i].y1-41){ //right side
            slidX=Pipes[i].x2-810;
            Character(position_x,position_y);            
        }
        else if (velocity_y>=0 && slidX>=Pipes[i].x1-840 && slidX<=Pipes[i].x2-810 && position_y>=Pipes[i].y1-58 && position_y<=Pipes[i].y1-41){ //make mario stay on top
            ObjectCollision=true;
            position_y=Pipes[i].y1-50;
            gravity=0;
            velocity_y=0;
            Character(position_x,position_y);
        }
    }
}

void GroundColl(){
        if (position_y<=510 && position_y>=490){ 
            //std::cout<< position_y << "\n";
            OnGround=true;
            position_y=500;
            velocity_y=0;
        }
}

void GravityCheck(){ //int &gravity
    if (gravity!=0.6f && (ObjectCollision==false || OnGround==false))
    {
        gravity=0.6f;
    }   
}

void UpdateFlags() //CAREFUL need to add flags.clear in LEVELS.h, level 2 has same flag and param right now
{
    for(int i=0; i<Flags.size(); i++)
    {
        int poleLeft  = Flags[i].x1 - 800;
        int poleRight = Flags[i].x2 - 800;


        if(Flags[i].PointChecked == false && slidX+50 > poleLeft && slidX < poleRight)
        {
            // after mario touches the pole I calculate points
            int section = (Flags[i].y2 - Flags[i].y1) / 3;

            int topThirdEnd = Flags[i].y1 + section;
            int midThirdEnd = Flags[i].y1 + section*2;

            if(position_y+50 <= topThirdEnd) {
                Point += 800;
            }
            else if(position_y+50 <= midThirdEnd) {
                Point += 500;
            }
            else {
                Point += 200;
            }

            Flags[i].PointChecked = true;

            // begin sliding animation
            //isSliding = true;
        }
        if(Flags[i].PointChecked == true && (slidX < Flags[i].x1-800)){
            slidX = poleLeft;
        }



        
            if(slidX+50 > poleLeft && slidX < poleRight)
            {
                // touching pole horizontally
                if(position_y+50 >= Flags[i].y1 && position_y < Flags[i].y2-50)
                {
                    // stop mario from moving through
                    slidX = poleLeft;
                }
            }
    }
}
