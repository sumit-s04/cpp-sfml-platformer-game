#include "Functions.h"

void NextLevel(){
    Blocks.clear();
    Goombas.clear();
    Holes.clear();
    Lands.clear();
    Clouds.clear();
    Pipes.clear();
    //Flags.clear();

    position_y=500;
    OnGround=true;
    ObjectCollision=false;

    sliderX=0;
    slidX=0;

    dClock.restart();

    for (int y=0; y<600; y++){
        for (int x = 0; x < 8000; x++){
            Dirt[y][x]=0;
        }
    }
    
    Level+=1;
    DrawLevel=true;

}

void Level1(){

        
    {
        int GREEN=100; 
        int BLUE=200; 

        for(int y=0; y<700; y++){
            if(y%50 == 0){
                GREEN+=4; 
                BLUE-=2;                 
            }
            for(int x=0; x<1600; x++){

                sky[y][x]=sf::Color(0, GREEN, BLUE).toInteger(); 
                    
            }
        }
    }

    Lvl1Textures();


        CreateDirt(0, 550, 8000);

        Castle(7400,200);

        Cloud(800,100);
        Cloud(300,0);
        Cloud(500,150);
        Cloud(1000,50);
        Cloud(675,25);
        Cloud(1150,160);
        Cloud(1300,100);        

        Cloud(1800,100);
        Cloud(2300,0);
        Cloud(1500,150);
        Cloud(2000,50);
        Cloud(1675,25);
        Cloud(2150,160);
        Cloud(3300,100);  

        Cloud(2800,100);
        Cloud(4300,0); //+2
        Cloud(2500,150);
        Cloud(3000,50);
        Cloud(2675,25);
        Cloud(3150,160);
        Cloud(5300,100);  //+2   
        
        Cloud(3800,100);
        Cloud(6300,0); //+2
        Cloud(3500,150);
        Cloud(4000,50);
        Cloud(3675,25);
        Cloud(4150,160);

        Cloud(4800,100);
        Cloud(7300,0); //+2
        Cloud(4500,150);
        Cloud(5000,50);
        Cloud(4675,25);
        Cloud(5150,160);

        Cloud(5800,100);
        Cloud(5500,150);
        Cloud(6000,50);
        Cloud(5675,25);
        Cloud(6150,160);

        Cloud(6500,150);
        Cloud(6675,25);
        Cloud(7575,125);
        Cloud(7875,25);



        Pipe(1090);
        Pipe(190);
        Pipe(2090);
        Pipe(1690);

        Pipe(2090);
        Pipe(3190);
        Pipe(2690);
        Pipe(4090);

        Pipe(4590);
        Pipe(4690);
        Pipe(4790);

        Pipe(5090);
        Pipe(6190);
        Pipe(7090);
        Pipe(5690);

        Pipe(6590);


        
        Block(350,800, true);             
        Block(350,910, false);             
        Block(250,1090, true);             
        Block(300,1990, false);             
        Block(250,2090, true);             
        Block(200,2190, false);             
        Block(325,1890, false);               

        Block(200,3190, false);             
        
        // floating Platform
        Block(250, 2500, false);
        Block(250, 2550, false);
        Block(250, 2600, false);

        Block(300, 2750, false);
        Block(300, 2800, false);
        Block(300, 2850, false);

        Block(200, 3050, false);
        Block(200, 3100, false);


        // wide platforma
        Block(350, 3600, true);
        Block(350, 3750, false);
        Block(350, 3900, false);

        Block(350, 3325, false);

        Block(250, 4650, true);
        Block(250, 4900, false);

        // towers
        Block(500, 4500, false);
        Block(450, 4500, false);
        Block(400, 4500, false);

        Block(500, 4350, false);
        Block(450, 4350, false);

        Block(500, 4200, false);
        Block(450, 4200, false);


        Block(200, 5100, false);
        Block(250, 5200, true);
        Block(300, 5300, false);
        Block(250, 5400, false);
        Block(300, 5500, true);
        Block(250, 5600, false);

        // make these hidden blocks above pit at 5750?
        Block(300, 5720, true);
        Block(300, 5780, false);
        Block(250, 5750, false);

        // high platform
        Block(250, 7000, false);
        Block(250, 7050, false);
        Block(250, 7100, true);
        Block(250, 7150, false);
        Block(250, 7200, false);

        // last floating platforms
        Block(300, 5950, true);
        Block(250, 6050, false);
        Block(200, 6150, false);

        Block(300, 6400, false);
        Block(300, 6450, false);
        Block(300, 6500, false);

        Block(350, 6700, false);
        Block(350, 6750, false);


        Hole(1750, 550);
        Hole(250, 550);
        Hole(5750, 550);
        Hole(3750, 550);
        Hole(6750, 550);

        Goomba(1200, 500, 1590);
        
        Goomba(2200, 500, 2590);
        Goomba(2500, 200, 2600);
        Goomba(3300, 500, 3690);
        Goomba(3375, 300, 3375);
        Goomba(3820, 500, 3970);
        Goomba(5200, 500, 5590);
        Goomba(6400, 500, 6450);
        Goomba(6400, 250, 6500);
        Goomba(6820, 500, 7000);
        Goomba(7000, 200, 7200);


        //Goomba(450, 500, 200);

        Flag(7250);

        for(int y=200; y<550; y++){ //FlagPole part 7250-7270 final pos
            for(int x=7250; x<7270; x++){
                Dirt[y][x]=sf::Color(200, 176, 26).toInteger(); 
            }
        }  

}

void Level2()
{
    // sky gradient (lvl 1-2 underground)
    {
        for (int y = 0; y < 700; y++) {
            for (int x = 0; x < 1600; x++) {
                sky[y][x] = sf::Color(0, 0, 0).toInteger();
            }
        }
    }

    // load textures for level 2
    Lvl2Textures();

    for (int y=550; y<600; y++){
        for (int x = 0; x < 8000; x++){
            Dirt[y][x]=sf::Color(2, 101, 102).toInteger();
        }
    }
    // base ground color (fill whole world)

    //CreateDirt(0, 550, 8000);

    // clouds 
    Cloud(300, 40);
    Cloud(700, 80);
    Cloud(1200, 20);
    Cloud(1700, 60);
    Cloud(2400, 30);
    Cloud(2900, 100);
    Cloud(3400, 30);
    Cloud(4100, 60);
    Cloud(4700, 90);
    Cloud(5200, 40);
    Cloud(5800, 60);
    Cloud(6400, 20);
    Cloud(7000, 80);
    Cloud(7600, 30);

    // Pipes some blocking safe landing zones
    Pipe(900);
    Pipe(1450);
    //Pipe(2250);
    Pipe(2650);
    Pipe(3050);
    Pipe(3650);
    Pipe(4450);
    Pipe(4950);
    Pipe(5550);
    Pipe(6150);
    Pipe(6850);

    // small pit sequence with low floating platform 
    Hole(1100, 550); // hole between pipes 
    Block(300, 1170, false); // small platform to jump to
    Block(300, 1220, false);
    Block(300, 1270, true);  

    // Platform stairs
    Block(400, 1700, false);
    Block(350, 1750, false);
    Block(300, 1800, false);
    Goomba(1850, 500, 2050);   // patrol under stairs
    Koopa(1800, 300, 1800);    // higher koopa on platform

    // Tight corridor with holes 
    Hole(2100, 550);
    Block(400, 2150, false);
    Block(400, 2200, true); // coin block on small step
    Hole(2320, 550);
    Block(400, 2360, false);

    // A cluster of floating platforms requiring chaining jumps
    Block(300, 2600, false);
    Block(300, 2650, true); // risky coin block
    Block(300, 2700, false);
    Block(300, 2750, false);
    //Goomba(2750, 500, 2950);
    Koopa(2600, 250, 2790); // koopa above, faster patrol


    Block(350, 3100, true); // reward at top
    Goomba(3150, 500, 3300);

    Koopa(3490, 500, 3650);
    Block(350, 3400, false);
    Block(350, 3620, false);
    Block(300, 3680, false);
    Block(300, 3740, true); // coin block

    // enemy cluster and a tighter pit
    Hole(3900, 550);
    Hole(3960, 550);
    Block(300, 4020, false);
    Goomba(4120, 500, 4300);

    // small floating platforms
    Koopa(4600, 325, 4880);
    Block(375, 4600, false);
    Block(375, 4650, false);
    Block(375, 4700, false);
    Block(375, 4750, false);
    Block(375, 4800, false);
    Koopa(4600, 500, 4800);

    
    Hole(5100, 550);
    Block(350, 5160, false);
    Block(200, 5180, true);
    Block(350, 5210, false);
    Hole(5280, 550);
    Block(300, 5350, false);

    // enemies in narrow path
    Block(400, 5600, false);
    Block(400, 5650, false);
    Goomba(5630, 500, 5890);
    Koopa(5720, 500, 6000);

    // clustered koopas and goombas
    Block(350, 6200, true);
    Block(350, 6250, false);
    Block(350, 6300, false);
    Koopa(6270, 500, 6490);
    Goomba(6350, 500, 6550);
    Koopa(6200, 300, 6350);

    Hole(6680, 550);
    Block(250, 6650, true); // reach via long jump 
    Block(250, 6710, false);

    // small step to flag
    Block(500, 7060, false);
    Block(500, 7100, false);
    Block(500, 7140, false);
    Block(125, 7180, true); // reward before flag
    Block(325, 7180, true); 
    Block(325, 7000, false);

    Goomba(7230, 275, 7230);


    Goomba(2750, 500, 2900);
    Goomba(5350, 500, 5500);
    Koopa(6920, 500, 7050);

    Hole(2950, 550);
    Hole(3420, 550);
    Hole(6050, 550);

    Castle(7400,60);
    Flag(7250);
}

/*void Level3(){

        
    {
        for(int y=0; y<700; y++){
            for(int x=0; x<1600; x++){

                sky[y][x]=sf::Color(0, 0, 0).toInteger(); 
                    
            }
        }
    }


    for (int y=550; y<600; y++){
        for (int x = 0; x < 8000; x++){
            Dirt[y][x]=sf::Color(50, 50, 50).toInteger();
        }
    }
    

        Koopa(1200, 500, 1590);
        Goomba(2200, 500, 2590);
        Goomba(2500, 200, 2600);
        Goomba(3300, 500, 3690);
        Goomba(3375, 300, 3375);
        Goomba(3820, 500, 3970);
        Goomba(5200, 500, 5590);
        Goomba(6400, 500, 6450);
        Goomba(6400, 250, 6500);
        Goomba(6820, 500, 7000);
        Goomba(7000, 200, 7200);


}*/