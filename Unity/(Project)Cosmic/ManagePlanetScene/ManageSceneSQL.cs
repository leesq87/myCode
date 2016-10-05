using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System;
using System.Data;
using Mono.Data.Sqlite;
using System.IO;

public class ManageSceneSQL : MonoBehaviour {

    string m_ConnectionString;
    string m_SQLiteFileName = "CosmicDB.sqlite";
    string conn;

    public static IDbConnection dbconn;
    public static IDbCommand dbcmd;
    public static IDataReader reader;



    void Awake()
    {
#if UNITY_EDITOR
        m_ConnectionString = "URI=file:" + Application.streamingAssetsPath + "/" + m_SQLiteFileName;
        //m_ConnectionString = "URI=file:" + Application.dataPath + "/" + m_SQLiteFileName;
#else
        // check if file exists in Application.persistentDataPath
        var filepath = string.Format("{0}/{1}", Application.persistentDataPath, m_SQLiteFileName);

        if (!File.Exists(filepath))
        {
            // if it doesn't ->
            // open StreamingAssets directory and load the db ->

#if UNITY_ANDROID
                WWW loadDb = new WWW("jar:file://" + Application.dataPath + "!/assets/" + m_SQLiteFileName);  // this is the path to your StreamingAssets in android
                loadDb.bytesDownloaded.ToString();
                while (!loadDb.isDone) { }  // CAREFUL here, for safety reasons you shouldn't let this while loop unattended, place a timer and error check
                // then save to Application.persistentDataPath
                File.WriteAllBytes(filepath, loadDb.bytes);
#elif UNITY_IOS
                     var loadDb = Application.dataPath + "/Raw/" + m_SQLiteFileName;  // this is the path to your StreamingAssets in iOS
                    // then save to Application.persistentDataPath
                    File.Copy(loadDb, filepath);
#elif UNITY_WP8
                    var loadDb = Application.dataPath + "/StreamingAssets/" + m_SQLiteFileName;  // this is the path to your StreamingAssets in iOS
                    // then save to Application.persistentDataPath
                    File.Copy(loadDb, filepath);
#elif UNITY_WINRT
      var loadDb = Application.dataPath + "/StreamingAssets/" + m_SQLiteFileName;  // this is the path to your StreamingAssets in iOS
      // then save to Application.persistentDataPath
      File.Copy(loadDb, filepath);
#else
            var loadDb = Application.dataPath + "/StreamingAssets/" + m_SQLiteFileName;  // this is the path to your StreamingAssets in iOS
                                                                                         // then save to Application.persistentDataPath
            File.Copy(loadDb, filepath);

#endif
        }

        m_ConnectionString = "URI=file:" + filepath;
#endif

        ///////////////////////////////////////////////////////////////////[DB Path]
        if (Application.platform == RuntimePlatform.Android)
        {
            conn = "URI=file:" + Application.persistentDataPath + "/CosmicDB.sqlite"; //Path to databse on Android
        }
        else { conn = "URI=file:" + Application.streamingAssetsPath + "/CosmicDB.sqlite"; } //Path to database Else
                                                                                            ///////////////////////////////////////////////////////////////////[DB Path]


        ///////////////////////////////////////////////////////////////////[DB Connection]
        dbconn = (IDbConnection)new SqliteConnection(conn);
        dbconn.Open(); //Open connection to the database.
        ///////////////////////////////////////////////////////////////////[DB Connection]

    }

    void Start()
    {
        settingInfo();

    }


    void settingInfo()
    {
        ///////////////////////////////////////////////////////////////////[DB Query]
        dbcmd = dbconn.CreateCommand();
        string sqlQuery = "SELECT count(*) FROM managePlanetTable";
        dbcmd.CommandText = sqlQuery;
        ///////////////////////////////////////////////////////////////////[DB Query]
        int cnt = 0;
        ///////////////////////////////////////////////////////////////////[Data Read]
        reader = dbcmd.ExecuteReader();
        //행성갯수 카운트
        while (reader.Read())
        {
            MovePlanet.Instance.planetCount = reader.GetInt32(cnt++);
        }

        reader.Close();
        reader = null;

        //각 행성 리스트로
        sqlQuery = "select rowid, name, size, color, mat, mFood, mTitanium, locationX, locationY, locationZ, le_persec, position_house, state, user, neighbor, lFood, lTitanium, tree1, tree2, tree3, tree4, tree5, tree6 FROM managePlanetTable WHERE user =0";
        dbcmd.CommandText = sqlQuery;
        reader = dbcmd.ExecuteReader();
        cnt = 0;
        while (reader.Read())
        {
            int rowid = reader.GetInt32(cnt++);
            string pName = reader.GetString(cnt++);
            int size = reader.GetInt32(cnt++);
            int color = reader.GetInt32(cnt++);
            int mat = reader.GetInt32(cnt++);
            int mFood = reader.GetInt32(cnt++);
            int mTitanium = reader.GetInt32(cnt++);
            float locationX = reader.GetFloat(cnt++);
            float locationY = reader.GetFloat(cnt++);
            float locationZ = reader.GetFloat(cnt++);
            int le_persec = reader.GetInt32(cnt++);
            bool position_house = reader.GetBoolean(cnt++);
            int state = reader.GetInt32(cnt++);
            bool user = reader.GetBoolean(cnt++);
            int neighbor = reader.GetInt32(cnt++);
            int lFood = reader.GetInt32(cnt++);
            int lTitanium = reader.GetInt32(cnt++);

            int tree1 = reader.GetInt32(cnt++);
            int tree2 = reader.GetInt32(cnt++);
            int tree3 = reader.GetInt32(cnt++);
            int tree4 = reader.GetInt32(cnt++);
            int tree5 = reader.GetInt32(cnt++);
            int tree6 = reader.GetInt32(cnt++);

            MovePlanet.Instance.getPlanets(color, size, mat, rowid);

            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().rowid = rowid;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().pName = pName;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().size = size;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().color = color;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().mat = mat;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().mFood = mFood;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().mTitanium = mTitanium;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().locationX = locationX;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().locationY = locationY;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().locationZ = locationZ;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().le_persec = le_persec;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().position_house = position_house;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().state = state;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().user = user;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().neighbor = neighbor;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().lFood = lFood;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().lTitanium = lTitanium;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().tree1 = tree1;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().tree2 = tree2;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().tree3 = tree3;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().tree4 = tree4;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().tree5 = tree5;
            GameObject.Find("RotatePlanet/" + rowid).GetComponent<PlanetInfo>().tree6 = tree6;

            cnt = 0;
        }

        reader.Close();
        reader = null;


        //유저있는행성불러오기
        sqlQuery = "select rowid, name, size, color, mat, mFood, mTitanium, locationX, locationY, locationZ, le_persec, position_house, state, user, neighbor, lFood, lTitanium, tree1, tree2, tree3, tree4, tree5, tree6 FROM managePlanetTable WHERE user = 1";
        dbcmd.CommandText = sqlQuery;
        reader = dbcmd.ExecuteReader();
        cnt = 0;
        while (reader.Read())
        {
            int rowid = reader.GetInt32(cnt++);
            string pName = reader.GetString(cnt++);
            int size = reader.GetInt32(cnt++);
            int color = reader.GetInt32(cnt++);
            int mat = reader.GetInt32(cnt++);
            int mFood = reader.GetInt32(cnt++);
            int mTitanium = reader.GetInt32(cnt++);
            float locationX = reader.GetFloat(cnt++);
            float locationY = reader.GetFloat(cnt++);
            float locationZ = reader.GetFloat(cnt++);
            int le_persec = reader.GetInt32(cnt++);
            bool position_house = reader.GetBoolean(cnt++);
            int state = reader.GetInt32(cnt++);
            bool user = reader.GetBoolean(cnt++);
            int neighbor = reader.GetInt32(cnt++);
            int lFood = reader.GetInt32(cnt++);
            int lTitanium = reader.GetInt32(cnt++);

            int tree1 = reader.GetInt32(cnt++);
            int tree2 = reader.GetInt32(cnt++);
            int tree3 = reader.GetInt32(cnt++);
            int tree4 = reader.GetInt32(cnt++);
            int tree5 = reader.GetInt32(cnt++);
            int tree6 = reader.GetInt32(cnt++);

            MovePlanet.Instance.nowPlanet(color, size, mat, rowid);

            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().rowid = rowid;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().pName = pName;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().size = size;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().color = color;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().mat = mat;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().mFood = mFood;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().mTitanium = mTitanium;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().locationX = locationX;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().locationY = locationY;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().locationZ = locationZ;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().le_persec = le_persec;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().position_house = position_house;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().state = state;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().user = user;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().neighbor = neighbor;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().lFood = lFood;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().lTitanium = lTitanium;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().tree1 = tree1;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().tree2 = tree2;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().tree3 = tree3;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().tree4 = tree4;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().tree5 = tree5;
            GameObject.Find("CurrentPlanet/Myplanet").GetComponent<PlanetInfo>().tree6 = tree6;

            cnt = 0;
        }

        reader.Close();
        reader = null;


        sqlQuery = "SELECT count(*) FROM zodiacTable WHERE find = 1 and active = 0";
        dbcmd.CommandText = sqlQuery;
        reader = dbcmd.ExecuteReader();
        //행성갯수  + 별 갯수
        while (reader.Read())
        {
            MovePlanet.Instance.planetCount += reader.GetInt32(cnt++);
            cnt = 0;
        }

        reader.Close();
        reader = null;

        sqlQuery = "SELECT rowid, name FROM zodiacTable WHERE find = 1 and active = 0";
        dbcmd.CommandText = sqlQuery;
        reader = dbcmd.ExecuteReader();
        //행성갯수  + 별 갯수
        while (reader.Read())
        {

            int rowid = reader.GetInt32(cnt++);
            string zName = reader.GetString(cnt++);

            MovePlanet.Instance.getStar(rowid);
            GameObject.Find("RotateStar/" + rowid).GetComponent<StarInfo>().rowid = rowid;
            GameObject.Find("RotateStar/" + rowid).GetComponent<StarInfo>().zName = zName;


            cnt = 0;
        }



        reader.Close();
        reader = null;


        sqlQuery = "SELECT * FROM userTable";
        dbcmd.CommandText = sqlQuery;
        reader = dbcmd.ExecuteReader();
        //유저정보
        cnt = 0;
        while (reader.Read())
        {
            MovePlanet.Instance.cPlanet = reader.GetInt32(cnt++);
            MovePlanet.Instance.cFood = reader.GetInt32(cnt++);
            MovePlanet.Instance.cTitanium = reader.GetInt32(cnt++);
            MovePlanet.Instance.cRE = reader.GetInt32(cnt++);
            MovePlanet.Instance.cYE = reader.GetInt32(cnt++);
            MovePlanet.Instance.cBE = reader.GetInt32(cnt++);
            MovePlanet.Instance.cOE = reader.GetInt32(cnt++);
            MovePlanet.Instance.cGE = reader.GetInt32(cnt++);
            MovePlanet.Instance.cVE = reader.GetInt32(cnt++);
            MovePlanet.Instance.cPE = reader.GetInt32(cnt++);
            MovePlanet.Instance.shipNum = reader.GetInt32(cnt++);

            cnt = 0;
        }
        MovePlanet.Instance.setShip(MovePlanet.Instance.shipNum);

        MovePlanet.Instance.setResource();

        reader.Close();
        reader = null;


        MovePlanet.Instance.setPlanets();
        MovePlanet.Instance.setDrag();

    }

    public void UpdateQuery(string ShipQuery)
    {
        dbcmd.CommandText = ShipQuery;
        dbcmd.ExecuteNonQuery();

        settingInfo();

    }

    public void UpdateQuery1(string Query)
    {
        dbcmd.CommandText = Query;
        dbcmd.ExecuteNonQuery();

    }

    public void DeleteQuery(string Query)
    {
        dbcmd.CommandText = Query;
        dbcmd.ExecuteNonQuery();

    }

    public void dbClose()
    {
        ///////////////////////////////////////////////////////////////////[DB Connection Close]
        //reader.Close();
        //reader = null;
        dbcmd.Dispose();
        dbcmd = null;
        dbconn.Close();
        dbconn = null;
        ///////////////////////////////////////////////////////////////////[DB Connection Close]
    }

}
