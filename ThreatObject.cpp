#include"ThreatObject.hpp"

ThreatObject::ThreatObject(){
    rect_.y = -72 ;
    rect_.x = SCREEN_WIDTH/10+ rand()% (SCREEN_WIDTH*8/10);
    rect_.w = THREAT_OBJECT_WIDTH;
    rect_.h = THREAT_OBJECT_HEIGHT;
    //4 Texture của threatobj
    rectTexture[0].x=0;
    rectTexture[0].y=0;
    rectTexture[0].w=106;
    rectTexture[0].h=185;

    rectTexture[1].x=106;
    rectTexture[1].y=0;
    rectTexture[1].w=106;
    rectTexture[1].h=185;

    rectTexture[2].x=106*2;
    rectTexture[2].y=0;
    rectTexture[2].w=106;
    rectTexture[2].h=185;

    rectTexture[3].x=106*3;
    rectTexture[3].y=0;
    rectTexture[3].w=106;
    rectTexture[3].h=185;

}
ThreatObject::~ThreatObject(){
}

void ThreatObject::GenerateBullet(SDL_Renderer* ren)
{
    EnemyBullet* enemy_bullet = new EnemyBullet();
    enemy_bullet->LoadImg("enemybullet.png",ren);
    enemy_bullet->SetRect( rect_.x + 34, rect_.y + THREAT_OBJECT_HEIGHT -2);
    int type;
    if(rand()%100<40){type=1;}
    else if(rand()%100>60) {type=2;}
    else type=0;
    enemy_bullet->SetBulletType(type);
    if(p_bullet_list.size()<=2) p_bullet_list.push_back(enemy_bullet); // giới hạn địch ra tối đa 3 đạn trong 1 khung hình
}

void ThreatObject::ControlBulletAndKillMainObject(int x, int y, SDL_Renderer* ren,
                                                  MainObject &main_object,Mix_Chunk* g_main_injured , GameText &Score)
{

    for (int i=0;i <p_bullet_list.size();i++ ) {
        if (p_bullet_list[i]->GetIsMove())
        {
            if (SDL_General::Do_two_objects_overlap( p_bullet_list[i]->GetRect(), main_object.GetRect() ) )
            {
                // update score
                Score.IncreaseValue(GET_INJURED_SCORE) ;
                // Play main_injured music.
                Mix_PlayChannel(-1,g_main_injured,0);
                main_object.SetIsShownInjured(true) ;
                main_object.ShowInjured(ren);
                main_object.DecreaseLives();
                delete p_bullet_list[i];
                p_bullet_list.erase( p_bullet_list.begin()+i );
            }
            else
            {
                p_bullet_list[i]->Show(ren);
                p_bullet_list[i]->HandleMove(x,y );
            }
        }
        else {
            delete p_bullet_list[i];
            p_bullet_list.erase( p_bullet_list.begin()+i );
            cout << p_bullet_list.size()<< endl ;
        }
    }
}

void ThreatObject::HandleMove(const int x_border, const int y_border) {
    if ( rect_.y > y_border ) {
        is_move = false;
        gofull=true;
    }
    int num = rand() % 5 ;
    switch(num)
    {
        case 0 :
             rect_.y+= THREAT_OBJECT_HEIGHT/15;
        break;

        case 1 :
            rect_.y+= THREAT_OBJECT_HEIGHT/15;
            rect_.x+= THREAT_OBJECT_WIDTH/8;
        break;

        case 2:
            rect_.y+= THREAT_OBJECT_HEIGHT/15;
            rect_.x-= THREAT_OBJECT_WIDTH/8;
        break;

        case 3:
            rect_.x-= THREAT_OBJECT_WIDTH/8;
        break;

        case 4:
            rect_.x+= THREAT_OBJECT_WIDTH/8;
        break;

    }

}
void ThreatObject::ShowAnimation(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, full_object_, &rectTexture[frame], &rect_);
    SDL_RenderPresent(ren);
    frame = (frame+1)%4;
}




