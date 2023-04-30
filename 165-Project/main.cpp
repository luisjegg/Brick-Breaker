#include<stdio.h>
#include<iostream>
#include<GL/glut.h>
#include<string>
#include<sstream>
#include<chrono>
#include<thread>
#include "Brickheader.h"
#include <vector>


using namespace std;

float barX = 200, barY = 465, barWidth = 80, barheight = 5;
float ballX = 235, ballY=430, ballWH = 10, ballVelX = 1.5, ballVelY = 1.5;
const int brickAmount = 100;
int score = 0, chances = 3, previousScore = 0, highestScore = 0;
bool flag = true, flag2 = true;
string powerUpMessage ;

struct bricks{
    float x;
    float y;
    float width;
    float height;
    bool isAlive= true;
    PowerUp* powerUp = nullptr;
};
bricks bricksArray[brickAmount];
vector<PowerUp*> powerUp;
void createBricks(){
    float brickX = 41, brickY = 0;
    for(int i=0;i<brickAmount;i++){
        if(brickX > 400){
            brickX = 41;
            brickY += 11;
        }
        bricksArray[i].x = brickX;
        bricksArray[i].y = brickY;
        bricksArray[i].width = 38.66;
        bricksArray[i].height = 10;
        brickX += 39.66;
        if (rand() % 20 == 0) {  
            int powerUpIndex = rand() % powerUp.size();
            bricksArray[i].powerUp = powerUp[powerUpIndex];
        }
    }
    glColor3ub(0,0,255);
    glBegin(GL_QUADS);
    for(int i=0;i<brickAmount;i++){
        if(bricksArray[i].isAlive == true){
            glVertex2f(bricksArray[i].x, bricksArray[i].y);
            glVertex2f(bricksArray[i].x + bricksArray[i].width, bricksArray[i].y);
            glVertex2f(bricksArray[i].x + bricksArray[i].width, bricksArray[i].y + bricksArray[i].height);
            glVertex2f(bricksArray[i].x, bricksArray[i].y + bricksArray[i].height);
          
        }
    }
    glEnd();
}

void print(const string& message) {
   glColor3f(1.0, 0.0, 0.0);
   glRasterPos2f(490, 20);
    int len1 = message.length();
    for(int i = 0; i < len1; i++){
        
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);
    }
    glColor3f(0.0, 0.0, 0.0);
    stringstream ss;
    ss << score;
    string s = "Score: "+ss.str();
    int len = s.length();
    glRasterPos2f(490, 70);
    for(int i = 0; i < len; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
    }

    stringstream ss2;
    ss2 << chances;
    string chance = "Lives left: "+ss2.str();
    glRasterPos2f(490, 100);
    for(int i = 0; i < chance.length(); i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, chance[i]);
    }

    stringstream ss3;
    ss3 << previousScore;
    string prevScore = "Previous score: "+ss3.str();
    glRasterPos2f(490, 130);
    for(int i = 0; i < prevScore.length(); i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, prevScore[i]);
    }

    stringstream ss4;
    ss4 << highestScore;
    string highScore = "Highest score: "+ss4.str();
    glRasterPos2f(490, 160);
    for(int i = 0; i < highScore.length(); i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, highScore[i]);
    }
}


void message(bool a){
    if(a == false){
        glRasterPos2f(20, 400);
        stringstream ss;
        ss << previousScore;
        string s = "Game over. Your score: "+ss.str()+". Click to start new game.";
        int len = s.length();
        for(int i = 0; i < len; i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
        }
    }
}

void completeMessage(bool a){
    if(a == false){
        glRasterPos2f(20, 400);
        stringstream ss;
        ss << score;
        string s = "STAGE COMPLETE. Your score: "+ss.str()+". Click to start new game.";
        int len = s.length();
        for(int i = 0; i < len; i++){
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]);
        }
    }
}



void myDisplay(void){
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);
    //Bar
    glBegin(GL_QUADS);
    glColor3ub(255, 204, 102);
    glVertex2f(barX, barY);
    glVertex2f(barX+barWidth, barY);
    glVertex2f(barX+barWidth, barY+barheight);
    glVertex2f(barX, barY+barheight);
    glEnd();
    
    
    //Ball
    glBegin(GL_QUADS);
    glColor3ub(255, 0, 0);
    glVertex2f(ballX, ballY);
    glVertex2f(ballX+ballWH, ballY);
    glVertex2f(ballX+ballWH, ballY+ballWH);
    glVertex2f(ballX, ballY+ballWH);
    glEnd();

    //sidebar
    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0);
    glVertex2f(480, 0);
    glVertex2f(480, 480);
    glVertex2f(485, 480);
    glVertex2f(485, 0);
    glEnd();

    glRasterPos2f(500, 430); 
    
    print(powerUpMessage);
    createBricks();
    message(flag);
    
    completeMessage(flag2);

    glutSwapBuffers();
}

void myInit (void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glViewport(0, 0, 760, 480);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 760.0, 480.0, 0.0);
}

bool checkCollision(float ballX, float ballY, float ballW, float ballH, float objX, float objY, float objW, float objH){
    bool hasCollision = false;
    // Check collision with bricks
    for (int i = 0; i < brickAmount; i++) {
        bricks& brick = bricksArray[i];
        if (brick.isAlive) {
            if (ballY + ballH < brick.y) {
                continue;
            }
            if (ballY > brick.y + brick.height) {
                continue;
            }
            if (ballX + ballW < brick.x) {
                continue;
            }
            if (ballX > brick.x + brick.width) {
                continue;
            }
            
            // A collision with a brick has occurred
            hasCollision = true;
            brick.isAlive = false;
            if (brick.powerUp != nullptr) {
                powerUpMessage = brick.powerUp->applyEffect();
                
            }
        }
    }

    // Check collision with bar
    if (ballY + ballH < objY) {
        return hasCollision;
    }
    if (ballY > objY + objH) {
        return hasCollision;
    }
    if (ballX + ballW < objX) {
        return hasCollision;
    }
    if (ballX > objX + objW) {
        return hasCollision;
    }

    // A collision with the bar has occurred
    return true;
}

void moveBall(){
    if(score >= 1000){
        barX = 200;
        barY = 465;
        ballX = 235;
        ballY = 430;
        ballVelX = 0;
        ballVelY = 0;
        float brickX = 2, brickY = 2;
        for(int i=0;i<brickAmount;i++){
            if(brickX > 450){
                brickX = 2;
                brickY += 11;
            }
            bricksArray[i].x = brickX;
            bricksArray[i].y = brickY;
            bricksArray[i].width = 38.66;
            bricksArray[i].height = 10;
            bricksArray[i].isAlive = true;
            brickX += 39.66;
        }
        previousScore = score;
        if(highestScore < score){
            highestScore = score;
        }
        chances = 3;
        score = 0;
        flag2 = false;
        this_thread::sleep_for(chrono::seconds(1));
        completeMessage(flag2);
    }
    else{
        ballX += ballVelX;
        for (int i=0; i<brickAmount; i++){
            if(bricksArray[i].isAlive == true){
                if(checkCollision(ballX, ballY, ballWH, ballWH, bricksArray[i].x, bricksArray[i].y, bricksArray[i].width, bricksArray[i].height) == true){
                    ballVelX = -ballVelX;
                    bricksArray[i].isAlive = true;
                    score += 10;
                    break;
                }
            }
        }
        ballY -= ballVelY;
  for (int i=0; i<brickAmount; i++){
            if(bricksArray[i].isAlive == true){
                if(checkCollision(ballX, ballY, ballWH, ballWH, bricksArray[i].x, bricksArray[i].y, bricksArray[i].width, bricksArray[i].height) == true){
                    ballVelY = -ballVelY;
                    bricksArray[i].isAlive = true;
                    score += 10;
                    break;
                }
            }
        }
        if(ballX < 0){
            ballVelX = -ballVelX;
        }
        else if(ballX+ballWH > 480){
            ballVelX = -ballVelX;
        }
        if(ballY < 0){
            ballVelY = -ballVelY;
        }
        else if(ballY+ballWH > 480){
            if(chances <= 1){
                barX = 200;
                barY = 465;
                ballX = 235;
                ballY = 430;
                ballVelX = 1.5;
                ballVelY = 1.5;
                float brickX = 2, brickY = 2;
                for(int i=0;i<brickAmount;i++){
                    if(brickX > 450){
                        brickX = 2;
                        brickY += 11;
                    }
                    bricksArray[i].x = brickX;
                    bricksArray[i].y = brickY;
                    bricksArray[i].width = 38.66;
                    bricksArray[i].height = 10;
                    bricksArray[i].isAlive = true;
                    brickX += 39.66;
                }
                previousScore = score;
                if(highestScore < score){
                    highestScore = score;
                }
                chances = 3;
                score = 0;
                flag = false;
                this_thread::sleep_for(chrono::seconds(1));
                message(flag);
            }
            else{
                chances--;
                ballX = 235;
                ballY=430;
                if(ballVelY < 0){
                    ballVelY = -ballVelY;
                }
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
        if(checkCollision(ballX, ballY, ballWH, ballWH, barX, barY, barWidth, barheight) == true){
            ballVelY = -ballVelY;
        }
    }
    glutPostRedisplay();
}

void keyboard(int key, int x, int y){
    switch(key){
        case GLUT_KEY_LEFT:
            barX -= 10;
            if(barX < 0){
                barX = 0;
            }
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            barX += 10;
            if(barX+barWidth > 480){
                barX = 480-barWidth;
            }
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

void mouse(int button,int state,int x,int y){
    switch(button){
        case GLUT_LEFT_BUTTON:
            if(state==GLUT_DOWN){
                flag = true;
                if(ballVelX <= 0 && ballVelY <= 0){
                    ballVelX = 0.3;
                    ballVelY = 0.3;
                }
                glutIdleFunc(moveBall);
            }
            break;
        default:
            break;
    }
}

// Reading part

int main(int argc, char** argv){
srand(time(nullptr));
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
glutInitWindowSize(760,480);
glutInitWindowPosition(100,150);
glutInit(&argc, argv);
glutCreateWindow("Brick Breaker");
powerUp.push_back(new SpeedBoost(0, 0));
powerUp.push_back(new ExtraLife(0, 0));
powerUp.push_back(new EnlargePaddle(0, 0));
powerUp.push_back(new Nothing(0, 0));
powerUp.push_back(new Nothing2(0, 0));
powerUp.push_back(new Nothing3(0, 0));
glutDisplayFunc(myDisplay);
glutSpecialFunc(keyboard);
glutMouseFunc(mouse);
myInit();
glutMainLoop();
    for (PowerUp* powerUp : powerUp) {
    powerUp->applyEffect();
}
    for (PowerUp* powerUp : powerUp) {
    delete powerUp;
}
powerUp.clear();

    return 0;
}


