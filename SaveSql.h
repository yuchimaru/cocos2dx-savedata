//
//  SaveSql.h
//  DayFantazyPj
//
//  Created by YuichiNishioka on 2014/06/22.
//
//

#ifndef __DayFantazyPj__SaveSql__
#define __DayFantazyPj__SaveSql__

#include "cocos2d.h"
#include "sqlite3.h"
#include <vector>
#define dbName "user_data.db"

class SaveSql : public cocos2d::Node {
    
    
public:

    // SQLのバインドがテキスト
    static const int SQLBIND_TEXT = 1;
    // SQLのバインドがINT
    static const int SQLBIND_INT = 2;

    // sql 用
    struct sqlValues{
        int valueType;
        char textVal;
    };
    
    virtual  bool init();
    
    
    static int sqliteOpen(sqlite3 **db);
    
    static void sqliteCreateTable(const char *sql_createtable);
    static const char* sqliteGetValueForKey(const char *key);
    static void sqliteSetValueForKey(const char *key,const char *value);
    
    static void sqliteUpdateValueForKey(const char *key,const char *value);
    // insert
    static void sqliteExec(const char *sql, std::vector<sqlValues> sqlVals);

};
#endif /* defined(__DayFantazyPj__SaveSql__) */
