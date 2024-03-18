#pragma once
#include "headers.h"

class Factory ;

class Mission {

    protected:

        string missionName ;
        int missionNum ;
        int casualEnemyNum ;
        int specialEnemyNum ;
        string story ;
        Factory* enemyBank ;
        Storage inventory ;
        Player* player ;
    
    public:

    // getters:


    // setters :


    //methods:
        void playerTurn();
        bool endTurn();
        void enemyTurn();
        void endWave();
        void removeDead();
        void playerDeath();
        void endMission();

};


class ZombieMission : public Mission {

};

class HumanMission : public Mission{

};

class Factory {
    protected:
        vector<vector<Character*>> enemies ;
        Mission mission ;

    public:
    // getters:

    // setters:

    //methods:

       vector<int> getWave();
       virtual void createEnemy() = 0 ;

};

class ZombieFactory : public Factory{
    public:
        void createEnemy() override ;
};

class HumanFactory : public Factory {
    public:
    void createEnemy() override ;
};

