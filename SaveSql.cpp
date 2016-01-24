//
//  SaveSql.cpp
//  DayFantazyPj
//
//  Created by YuichiNishioka on 2014/06/22.
//
//

#include "SaveSql.h"
#include <vector>
USING_NS_CC;

//データベースを開く
int SaveSql::sqliteOpen(sqlite3 **db){
    
    auto filePath = FileUtils::getInstance()->getWritablePath();
    filePath += dbName;
    
    
    return sqlite3_open(filePath.c_str(),db);
    
}


//データベースのテーブルの作成
void SaveSql::sqliteCreateTable(const char *sql_createtable){
    
    //データベースを作成
    sqlite3 *db = NULL;
    if(sqliteOpen(&db) == SQLITE_OK){
        
        sqlite3_stmt *stmt = NULL;
        if (sqlite3_prepare_v2(db, sql_createtable, -1, &stmt, NULL) == SQLITE_OK) {
            
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                
                CCLOG("create table done");
            }
            
            sqlite3_reset(stmt);
            
            
        }
        
        sqlite3_finalize(stmt);
        
        
        
    }

    sqlite3_close(db);

}


//keyから値を取り出す。
const char *SaveSql::sqliteGetValueForKey(const char *key){
    
    __String *strValue = NULL;
    sqlite3 *db = NULL;
    if (sqliteOpen(&db) == SQLITE_OK) {
        
        //test1テーブルからkeyに合わせたvalueを取り出す
        const char *sql_select = "SELECT value FROM test1 WHERE key=?";
        sqlite3_stmt *stmt = NULL;
        if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) == SQLITE_OK) {
            
            sqlite3_bind_text(stmt, 1, key, -1, SQLITE_TRANSIENT);
            int ret = sqlite3_step(stmt);
            if (ret == SQLITE_DONE || ret == SQLITE_ROW) {
                
                const char *val = (const char*)sqlite3_column_text(stmt, 0);
                strValue = __String::create(val);
                
            }
            
            sqlite3_reset(stmt);
            
        }
        
        sqlite3_finalize(stmt);
        
    }
    
    sqlite3_close(db);
    
    
    //valueがある場合
    if (strValue != NULL) {
        
        return strValue->getCString();
    }
    
    return NULL;
}


//keyとvalueを設定する(初期)
void SaveSql::sqliteSetValueForKey(const char *key,const char *value){
    
    
    std::string fullpath = CCFileUtils::getInstance()->getWritablePath();
    fullpath += dbName;
    sqlite3 *db = NULL;
    
    if (sqlite3_open(fullpath.c_str(), &db) == SQLITE_OK) {
        
        const char *sql_select = "REPLACE INTO test1(key,value)VALUES(?,?)";
        sqlite3_stmt *stmt = NULL;
        
        if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) == SQLITE_OK) {
            
            sqlite3_bind_text(stmt, 1, key, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, value, -1, SQLITE_TRANSIENT);
            
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                
                CCLOG("replace key:%s value:%s",key,value);
                
            }
            
            sqlite3_reset(stmt);
            
        }
        
        sqlite3_finalize(stmt);
        
    }
    
    sqlite3_close(db);
    
    
}


//keyを元にValueの値を更新する
void SaveSql::sqliteUpdateValueForKey(const char *key,const char *value){
    
    
    std::string fullpath = CCFileUtils::getInstance()->getWritablePath();
    fullpath += dbName;
    sqlite3 *db = NULL;
    
    if (sqlite3_open(fullpath.c_str(), &db) == SQLITE_OK) {
        
        const char *sql_select = "UPDATE test1 SET value =? WHERE key =? ";
        sqlite3_stmt *stmt = NULL;
        
        if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) == SQLITE_OK) {
            
            sqlite3_bind_text(stmt, 1, value, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, key, -1, SQLITE_TRANSIENT);
            
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                
                CCLOG("change key:%s value:%s",key,value);
                
            }
            
            sqlite3_reset(stmt);
            
        }
        
        sqlite3_finalize(stmt);
        
    }
    
    sqlite3_close(db);
    
    
}


//keyを元にValueの値を更新する
void SaveSql::sqliteExec(const char *sql, std::vector<sqlValues> sqlVals){

    std::string fullpath = CCFileUtils::getInstance()->getWritablePath();
    fullpath += dbName;
    sqlite3 *db = NULL;
    
    if (sqlite3_open(fullpath.c_str(), &db) == SQLITE_OK) {

        sqlite3_stmt *stmt = NULL;
        
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
            int count = 1;
            for (std::vector<sqlValues>::const_iterator it = sqlVals.begin(); it != sqlVals.end (); it++)
            {
                if(it->valueType == SQLBIND_TEXT){
                    sqlite3_bind_text(stmt, count, &it->textVal, -1, SQLITE_TRANSIENT);
                }else if(it->valueType == SQLBIND_INT){
                    sqlite3_bind_int(stmt, count, it->textVal);
                }
                count++;
            }
            
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                CCLOG("step ok");
            }
            
            sqlite3_reset(stmt);
            
        }
        
        sqlite3_finalize(stmt);
        
    }
    
    sqlite3_close(db);
    
    
}
