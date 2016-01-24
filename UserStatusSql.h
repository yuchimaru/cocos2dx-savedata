//
//  UserStatusSql.h
//  DayFantazyPj
//
//  Created by YuichiNishioka on 2014/10/17.
//
//

#ifndef __DayFantazyPj__UserStatusSql__
#define __DayFantazyPj__UserStatusSql__

#include "cocos2d.h"
#include "SaveSql.h"
#include <vector>
#include <iostream>

class UserStatusSql : public SaveSql {
public:
    static void createTable();

    typedef struct _userStatusColumn{
        int user_id;
        const char *name;
        int level;
        int hp;
        int mp;
        int gold;
        int exp;
        int stage_id;
        int max_meter;
        int max_slash;
        int strength;
        const char *login_date;
        const char *save_date;
        const char *first_date;
    } userStatusColumn;

    static userStatusColumn selectUserStatusForUid(int user_id);

    static void insertTable(userStatusColumn userStatusData);

    static void updateTable(int user_id, int level, int hp, int mp, int gold, int exp);
    
    static void updateStageId(int user_id, int stage_id);
    
    static void updateHpUp(int user_id, int gold, int hp);
    
    static void updateGoldUp(int user_id, int gold);

    static void updateMpUp(int user_id, int gold, int mp);

    static void updateStrengthUp(int user_id, int gold, int strength);

    static void updateStageEnd(int user_id, int stage_id, int gold, int max_meter, int max_slash);
};

#endif /* defined(__DayFantazyPj__UserStatusSql__) */
