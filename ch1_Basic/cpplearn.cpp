#include "cpplearn.h"
class CBaseTest{
public:
    CBaseTest()
    {
        cout << "CTest" << endl;
    }
    ~CBaseTest()
    {
        cout << "~CTest" << endl;
    }
public:
    virtual void TestVirtual();
};

class CBase1 :public CBaseTest
{
public:
    CBase1(){}
    ~CBase1(){}
};

class CFloorSexPair
{
public:
    CFloorSexPair() :m_sFloorid("0"), m_sSex("0") {}
    ~CFloorSexPair(){}
public:
    string m_sFloorid;
    string m_sSex;
};

struct CFloorSexPairCompare
{
    bool operator() (const CFloorSexPair& lhs, const CFloorSexPair& rhs) const
    {
        uint32_t dwlFloorid = strtoul(lhs.m_sFloorid.c_str(), NULL, 10);
        uint32_t dwrFloorid = strtoul(rhs.m_sFloorid.c_str(), NULL, 10);
        uint32_t dwlSex = strtoul(lhs.m_sSex.c_str(), NULL, 10);
        uint32_t dwrSex = strtoul(rhs.m_sSex.c_str(), NULL, 10);
        bool btest = dwlFloorid < dwrFloorid || dwlSex < dwrSex;
        //return dwlFloorid < dwrFloorid || dwlSex < dwrSex ;
        if (dwlFloorid == dwrFloorid){
            return dwlSex < dwrSex;
        }
        else{
            return dwlFloorid < dwrFloorid;
        }
        //|| dwlSex < dwrSex;
    }
};

void ResolveSceneId(const uint64_t ddwSceneId, uint16_t & usHigh, uint16_t & usMid, uint32_t & dwLow){
    int16_t sMid = -1;
    int32_t iLow = -1;
    usHigh = ddwSceneId >> 48;
    usMid = (ddwSceneId >> 32) & sMid;
    dwLow = ddwSceneId & iLow;
}

void ComputeDayofWeek()
{
    struct tm timeinfo;
    time_t tt;
    time(&tt);
    localtime_s(&timeinfo, &tt);
    // print zero based day of week
    printf("day of week = %d\n", timeinfo.tm_wday);
}
void TestResolveSceneId()
{
    uint64_t ddwSceneid = 844710708678038213;
    uint16_t ush, usm;
    uint32_t dwl;
    ResolveSceneId(ddwSceneid, ush, usm, dwl);
    cout << ush << " " << usm << " " << dwl << endl;
}
const string GetHi()
{
    stringstream ssHi;
    string s1 = "gao";
    string s2 = "yang";
    ssHi << s1 << "+" << s2;
    return ssHi.str();
}

void IsWhiteUser(const string& sPin, const string& sWhitelist)
{
    bool m_bWhiteUser;
    string m_sWhiteFloorSeq;
    if (sPin.empty()){
        m_bWhiteUser = false;
    }
    size_t dwUserIdPosition, dwCommaPosition, dwDelimPosition;
    dwUserIdPosition = sWhitelist.find("|" + sPin + ",");
    if (dwUserIdPosition != std::string::npos){
        m_bWhiteUser = true;
        dwCommaPosition = sWhitelist.find(",", dwUserIdPosition + 1);
        dwDelimPosition = sWhitelist.find("|", dwUserIdPosition + 1);
        m_sWhiteFloorSeq = sWhitelist.substr(dwCommaPosition + 1, dwDelimPosition - dwCommaPosition - 1);
        cout << m_sWhiteFloorSeq << " " << m_sWhiteFloorSeq.size() << endl;
    }
    else
    {
        m_bWhiteUser = false;
    }

}
//#pragma pack(4)
struct structTest1
{
    char c1;
    short s1;
    int i1;
};

struct structTest2
{
    char c2;
    int i2;
    short s2;

};

void Test_CFloorSexPair()
{
    map<CFloorSexPair, string, CFloorSexPairCompare> mapTest;
    CFloorSexPair oPair1;
    oPair1.m_sSex = "0";
    oPair1.m_sFloorid = "0";
    mapTest[oPair1] = "0,0";

    CFloorSexPair oPair2;
    oPair2.m_sSex = "0";
    oPair2.m_sFloorid = "1";
    mapTest[oPair2] = "0,1";

    CFloorSexPair oPair3;
    oPair3.m_sSex = "1";
    oPair3.m_sFloorid = "0";
    mapTest[oPair3] = "1,0";

    CFloorSexPair oPair4;
    oPair4.m_sSex = "1";
    oPair4.m_sFloorid = "1";
    mapTest[oPair4] = "1,1";
    /*
    CFloorSexPair oPair2;
    oPair2.m_sSex = "0";
    oPair2.m_sFloorid = "1";
    mapTest[oPair2] = "0,1";

    CFloorSexPair oPair3;
    oPair3.m_sSex = "1";
    oPair3.m_sFloorid = "0";
    mapTest[oPair3] = "1,0";

    CFloorSexPair oPair4;
    oPair4.m_sSex = "1";
    oPair4.m_sFloorid = "1";
    mapTest[oPair4] = "1,1";
    */
    cout << "1 " << mapTest[oPair1] << endl;
    cout << "2 " << mapTest[oPair2] << endl;
    cout << "3 " << mapTest[oPair3] << endl;
    cout << "4 " << mapTest[oPair4] << endl;
    cout << mapTest.size() << endl;
    /*
    cout << "2 " << mapTest[oPair2] << endl;
    cout << "3 " << mapTest[oPair3] << endl;
    cout << "4 " << mapTest[oPair4] << endl;
    */

    /*
    map<string, string> mTest;
    mTest["0,0"] = "0,0";
    mTest["0,1"] = "0,1";
    mTest["1,0"] = "1,0";
    mTest["1,1"] = "1,1";
    cout << mTest.size() << endl;
    */
}
void Test_IsWhiteUser()
{
    string sPin = "1q2w3e4r6y";
    string sList = "|1q2w3e4r5t,4,3,5,2,1|1q2w3e4r6y,1,2,3,4,5|";
    IsWhiteUser(sPin, sList);
}

void Test_mapIndex()
{
    map<uint32_t, uint32_t> mapTest;
    mapTest[1] = 2;
    cout << mapTest[0] << endl;
    cout << mapTest.size() << endl; // 如果关键字不在map中, 会创建 (0 - 0)的元素
}

int main()
{
    cout << "hello" << endl;
    return 0;
}