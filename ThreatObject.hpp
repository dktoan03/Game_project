#ifndef THREATOBJECT_H_
#define THREATOBJECT_H_

#include"BaseObject.hpp"
#include"MainObject.hpp"
#include"EnemyBullet.hpp"
#include"GameText.hpp"
// 106 185
const double THREAT_OBJECT_WIDTH = 80.2162;
const double THREAT_OBJECT_HEIGHT = 140;

class ThreatObject: public BaseObject
{
public:
    ThreatObject();
    ~ThreatObject();
    void HandleMove(const int x_border, const int y_border);
    void GenerateBullet(SDL_Renderer* ren );
    void ControlBulletAndKillMainObject(int x, int y,SDL_Renderer* ren, MainObject &main_object,Mix_Chunk* g_main_injured, GameText &Score );
    bool GetIsMove() {return is_move ;};
    bool Getgofull(){return gofull;};
    std::vector <EnemyBullet*> GetBulletList() { return p_bullet_list; };
    void SetBulletList( std::vector <EnemyBullet*> bullet ){ p_bullet_list = bullet;  };
    void ShowAnimation(SDL_Renderer* ren);
private:
    bool is_move = 1,gofull=0;
    vector <EnemyBullet*> p_bullet_list;
    SDL_Rect rectTexture[4];
    int frame = 0;
};
#endif // THREATOBJECT_H_
