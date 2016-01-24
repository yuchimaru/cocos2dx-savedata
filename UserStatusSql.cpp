//
//  UserStatusSql.cpp
//  DayFantazyPj
//
//  Created by YuichiNishioka on 2014/10/17.
//
//

#include "UserStatusSql.h"
#include "SaveSql.h"
#define dbName "user_data.db"

USING_NS_CC;

void UserStatusSql::createTable(){
    // tables
    const char *create_user_status_table = "CREATE TABLE user_status(user_id INTEGER PRIMARY KEY, name TEXT, level INTEGER, hp INTEGER, mp INTEGER, gold INTEGER, exp INTEGER, stage_id INTEGER, max_meter INTEGER, max_slash INTEGER, strength INTEGER, login_date TEXT, save_date TEXT, first_date TEXT)";
    
    // table create
    SaveSql::sqliteCreateTable(create_user_status_table);

}



//keyから値を取り出す。
UserStatusSql::userStatusColumn UserStatusSql::selectUserStatusForUid(int user_id){

    std::string fullpath = CCFileUtils::getInstance()->getWritablePath();
    fullpath += dbName;

    sqlite3 *db = NULL;
    userStatusColumn retUserStatus;

    if (sqlite3_open(fullpath.c_str(), &db) == SQLITE_OK) {
        
        //test1テーブルからkeyに合わせたvalueを取り出す
        const char *sql_select = "SELECT * FROM user_status WHERE user_id=?";
        sqlite3_stmt *stmt = NULL;

        if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) == SQLITE_OK) {
            
            sqlite3_bind_int(stmt, 1, user_id);

            int ret = sqlite3_step(stmt);
            if (ret == SQLITE_DONE || ret == SQLITE_ROW) {
                
                std::string name = (const char *)sqlite3_column_text(stmt, 1);
                std::string login_date = (const char *)sqlite3_column_text(stmt, 11);
                std::string save_date = (const char *)sqlite3_column_text(stmt, 12);
                std::string first_date = (const char *)sqlite3_column_text(stmt, 13);

                retUserStatus = {
                    sqlite3_column_int(stmt, 0),
                    name.c_str(),
                    sqlite3_column_int(stmt, 2),
                    sqlite3_column_int(stmt, 3),
                    sqlite3_column_int(stmt, 4),
                    sqlite3_column_int(stmt, 5),
                    sqlite3_column_int(stmt, 6),
                    sqlite3_column_int(stmt, 7),
                    sqlite3_column_int(stmt, 8),
                    sqlite3_column_int(stmt, 9),
                    sqlite3_column_int(stmt, 10),
                    login_date.c_str(),
                    save_date.c_str(),
                    first_date.c_str()
                };
 
            }

            sqlite3_reset(stmt);

        }
        
        sqlite3_finalize(stmt);
        
    }
    
    sqlite3_close(db);

    return retUserStatus;
}

//Insert
void UserStatusSql::insertTable(userStatusColumn userStatusData){
    
    const char *sql = "INSERT INTO user_status VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?)";

    std::string fullpath = CCFileUtils::getInstance()->getWritablePath();
    fullpath += dbName;
    sqlite3 *db = NULL;
    
    if (sqlite3_open(fullpath.c_str(), &db) == SQLITE_OK) {
        
        sqlite3_stmt *stmt = NULL;
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            sqlite3_bind_int(stmt,  1, userStatusData.user_id);
            sqlite3_bind_text(stmt, 2, userStatusData.name, -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt,  3, userStatusData.level);
            sqlite3_bind_int(stmt,  4, userStatusData.hp);
            sqlite3_bind_int(stmt,  5, userStatusData.mp);
            sqlite3_bind_int(stmt,  6, userStatusData.gold);
            sqlite3_bind_int(stmt,  7, userStatusData.exp);
            sqlite3_bind_int(stmt,  8, userStatusData.stage_id);
            sqlite3_bind_int(stmt,  9, userStatusData.max_meter);
            sqlite3_bind_int(stmt,  10, userStatusData.max_slash);
            sqlite3_bind_int(stmt,  11, userStatusData.strength);
            sqlite3_bind_text(stmt, 12, userStatusData.login_date, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 13, userStatusData.save_date, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 14, userStatusData.first_date, -1, SQLITE_TRANSIENT);
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                CCLOG("step ok");
            }
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}

//Update
void UserStatusSql::updateTable(int user_id, int level, int hp, int mp, int gold, int exp){
    
    const char *sql = "UPDATE user_status SET level = ?, hp = ?, mp = ?, gold = ?, exp = ? WHERE user_id = ?";
    
    std::string fullpath = CCFileUtils::getInstance()->getWritablePath();
    fullpath += dbName;
    sqlite3 *db = NULL;
    
    if (sqlite3_open(fullpath.c_str(), &db) == SQLITE_OK) {
        
        sqlite3_stmt *stmt = NULL;
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {

            sqlite3_bind_int(stmt,  1, level);
            sqlite3_bind_int(stmt,  2, hp);
            sqlite3_bind_int(stmt,  3, mp);
            sqlite3_bind_int(stmt,  4, gold);
            sqlite3_bind_int(stmt,  5, exp);
            sqlite3_bind_int(stmt,  6, user_id);

           if (sqlite3_step(stmt) == SQLITE_DONE) {
                CCLOG("step ok");
            }
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}

//story
void UserStatusSql::updateStageId(int user_id, int stage_id){
    
    const char *sql = "UPDATE user_status SET stage_id = ? WHERE user_id = ?";
    
    std::string fullpath = CCFileUtils::getInstance()->getWritablePath();
    fullpath += dbName;
    sqlite3 *db = NULL;
    
    if (sqlite3_open(fullpath.c_str(), &db) == SQLITE_OK) {
        
        sqlite3_stmt *stmt = NULL;
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            
            sqlite3_bind_int(stmt,  1, stage_id);
            sqlite3_bind_int(stmt,  2, user_id);
            
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                CCLOG("step ok");
            }
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}

void UserStatusSql::updateHpUp(int user_id, int gold, int hp){
    
    const char *sql = "UPDATE user_status SET gold = ?, hp = ? WHERE user_id = ?";
    
    std::string fullpath = CCFileUtils::getInstance()->getWritablePath();
    fullpath += dbName;
    sqlite3 *db = NULL;
    
    if (sqlite3_open(fullpath.c_str(), &db) == SQLITE_OK) {
        
        sqlite3_stmt *stmt = NULL;
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            
            sqlite3_bind_int(stmt,  1, gold);
            sqlite3_bind_int(stmt,  2, hp);
            sqlite3_bind_int(stmt,  3, user_id);
            
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                CCLOG("step ok");
            }
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}

void UserStatusSql::updateGoldUp(int user_id, int gold){
    
    const char *sql = "UPDATE user_status SET gold = gold + ?, hp = ? WHERE user_id = ?";
    
    std::string fullpath = CCFileUtils::getInstance()->getWritablePath();
    fullpath += dbName;
    sqlite3 *db = NULL;
    
    if (sqlite3_open(fullpath.c_str(), &db) == SQLITE_OK) {
        
        sqlite3_stmt *stmt = NULL;
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            
            sqlite3_bind_int(stmt,  1, gold);
            sqlite3_bind_int(stmt,  2, user_id);
            
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                CCLOG("step ok");
            }
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}

void UserStatusSql::updateMpUp(int user_id, int gold, int mp){
    
    const char *sql = "UPDATE user_status SET gold = ?, mp = ? WHERE user_id = ?";
    
    std::string fullpath = CCFileUtils::getInstance()->getWritablePath();
    fullpath += dbName;
    sqlite3 *db = NULL;
    
    if (sqlite3_open(fullpath.c_str(), &db) == SQLITE_OK) {
        
        sqlite3_stmt *stmt = NULL;
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            
            sqlite3_bind_int(stmt,  1, gold);
            sqlite3_bind_int(stmt,  2, mp);
            sqlite3_bind_int(stmt,  3, user_id);
            
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                CCLOG("step ok");
            }
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}

void UserStatusSql::updateStrengthUp(int user_id, int gold, int strength){
    
    const char *sql = "UPDATE user_status SET gold = ?, strength = ? WHERE user_id = ?";
    
    std::string fullpath = CCFileUtils::getInstance()->getWritablePath();
    fullpath += dbName;
    sqlite3 *db = NULL;
    
    if (sqlite3_open(fullpath.c_str(), &db) == SQLITE_OK) {
        
        sqlite3_stmt *stmt = NULL;
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            
            sqlite3_bind_int(stmt,  1, gold);
            sqlite3_bind_int(stmt,  2, strength);
            sqlite3_bind_int(stmt,  3, user_id);
            
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                CCLOG("step ok");
            }
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}

void UserStatusSql::updateStageEnd(int user_id, int stage_id, int gold, int max_meter, int max_slash){
    
    const char *sql = "UPDATE user_status SET stage_id = ?, gold = ?, max_meter = ? , max_slash = ? WHERE user_id = ?";
    
    std::string fullpath = CCFileUtils::getInstance()->getWritablePath();
    fullpath += dbName;
    sqlite3 *db = NULL;
    
    if (sqlite3_open(fullpath.c_str(), &db) == SQLITE_OK) {
        
        sqlite3_stmt *stmt = NULL;
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            
            sqlite3_bind_int(stmt,  1, stage_id);
            sqlite3_bind_int(stmt,  2, gold);
            sqlite3_bind_int(stmt,  3, max_meter);
            sqlite3_bind_int(stmt,  4, max_slash);
            sqlite3_bind_int(stmt,  5, user_id);
            
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                CCLOG("step ok");
            }
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}