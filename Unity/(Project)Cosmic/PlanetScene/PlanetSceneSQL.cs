using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Collections;
using System;
using System.Data;
using Mono.Data.Sqlite;
using System.IO;


public class PlanetSceneSQL : MonoBehaviour {
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
        string sqlQuery = "SELECT * FROM userTable";
        dbcmd.CommandText = sqlQuery;
        ///////////////////////////////////////////////////////////////////[DB Query]
        int cnt = 0;
        ///////////////////////////////////////////////////////////////////[Data Read]
        reader = dbcmd.ExecuteReader();
        while (reader.Read())
        {

            PlanetSceneSingleTon.Instance.cPlanet = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.cFood = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.cTitanium = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.cRE = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.cYE = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.cBE = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.cOE = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.cGE = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.cVE = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.cPE = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.shipNum = reader.GetInt32(cnt++);

        }
        reader.Close();
        reader = null;

        if (gameObject.scene.name == "Defense")
        {
            sqlQuery = "select rowid, * from managePlanetTable where rowid = " + GameObject.Find("OBJ").GetComponent<OBJScript>().rowid;
        }
        else {
            sqlQuery = "select rowid, * from managePlanetTable where user = 1";
        }
        dbcmd.CommandText = sqlQuery;
        reader = dbcmd.ExecuteReader();
        cnt = 0;
        while (reader.Read())
        {
            PlanetSceneSingleTon.Instance.rowid = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.pName = reader.GetString(cnt++);
            PlanetSceneSingleTon.Instance.size = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.color = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.mat = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.mFood = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.mTitanium = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.locationX = reader.GetFloat(cnt++);
            PlanetSceneSingleTon.Instance.locationY = reader.GetFloat(cnt++);
            PlanetSceneSingleTon.Instance.locationZ = reader.GetFloat(cnt++);
            PlanetSceneSingleTon.Instance.le_persec = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.position_house = reader.GetBoolean(cnt++);
            PlanetSceneSingleTon.Instance.state = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.user = reader.GetBoolean(cnt++);
            PlanetSceneSingleTon.Instance.neighbor = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.lFood = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.lTitanium = reader.GetInt32(cnt++);

            PlanetSceneSingleTon.Instance.planetTouchT = reader.GetString(cnt++);
            PlanetSceneSingleTon.Instance.titaniumTouchT = reader.GetString(cnt++);
            PlanetSceneSingleTon.Instance.treeTouchT = reader.GetString(cnt++);
            PlanetSceneSingleTon.Instance.breaktime = reader.GetString(cnt++);

            PlanetSceneSingleTon.Instance.tree1 = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.tree2 = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.tree3 = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.tree4 = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.tree5 = reader.GetInt32(cnt++);
            PlanetSceneSingleTon.Instance.tree6 = reader.GetInt32(cnt++);

        }

        reader.Close();
        reader = null;
        //dbClose();
        PlanetSceneSingleTon.Instance.callPlanet();
        PlanetSceneSingleTon.Instance.callShip();
        PlanetSceneSingleTon.Instance.callTree();
        PlanetSceneSingleTon.Instance.callNeighber();
        PlanetSceneSingleTon.Instance.callStation();
        PlanetSceneSingleTon.Instance.callPlanet();
        PlanetSceneSingleTon.Instance.callPostBox();
        PlanetSceneSingleTon.Instance.setVisibleEnergyBtn();
        PlanetSceneSingleTon.Instance.setVisibleMoveBtn();
    }



    public void UpdateQuery(string ShipQuery)
    {
        dbcmd.CommandText = ShipQuery;
        dbcmd.ExecuteNonQuery();

        settingInfo();

    }

     public void dbClose()
    {
        ///////////////////////////////////////////////////////////////////[DB Connection Close]
//        reader.Close();
 //       reader = null;
        dbcmd.Dispose();
        dbcmd = null;
        dbconn.Close();
        dbconn = null;
        ///////////////////////////////////////////////////////////////////[DB Connection Close]
    }

}
