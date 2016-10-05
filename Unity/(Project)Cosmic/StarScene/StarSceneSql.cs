using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System;
using System.Data;
using Mono.Data.Sqlite;
using System.IO;


public class StarSceneSql : MonoBehaviour
{
    string m_ConnectionString;
    string m_SQLiteFileName = "CosmicDB.sqlite";
    string conn;

    public static IDbConnection dbconn;
    public static IDbCommand dbcmd ;
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

    public static void StarStart()
    {
        ///////////////////////////////////////////////////////////////////[DB Query]
        dbcmd = dbconn.CreateCommand();
        string sqlQuery = "SELECT * FROM userTable";
        dbcmd.CommandText = sqlQuery;
        ///////////////////////////////////////////////////////////////////[DB Query]

        int cnt = 0;
        reader = dbcmd.ExecuteReader();
        while (reader.Read())
        {
            StarSingleTon.Instance.cPlanet = reader.GetInt32(cnt++);
            StarSingleTon.Instance.cFood = reader.GetInt32(cnt++);
            StarSingleTon.Instance.cTitanium = reader.GetInt32(cnt++);
            StarSingleTon.Instance.cRE = reader.GetInt32(cnt++);
            StarSingleTon.Instance.cYE = reader.GetInt32(cnt++);
            StarSingleTon.Instance.cBE = reader.GetInt32(cnt++);
            StarSingleTon.Instance.cOE = reader.GetInt32(cnt++);
            StarSingleTon.Instance.cGE = reader.GetInt32(cnt++);
            StarSingleTon.Instance.cVE = reader.GetInt32(cnt++);
            StarSingleTon.Instance.cPE = reader.GetInt32(cnt++);
            StarSingleTon.Instance.shipNum = reader.GetInt32(cnt++);

            cnt = 0;
        }
        cnt = 0;

        reader.Close();
        reader = null;

        sqlQuery = "SELECT * FROM zodiacTable WHERE rowid =" + StarSingleTon.Instance.rowid;

        dbcmd.CommandText = sqlQuery;
        reader = dbcmd.ExecuteReader();
        while (reader.Read())
        {
            StarSingleTon.Instance.zID = reader.GetString(cnt++);
            StarSingleTon.Instance.zodiac = reader.GetString(cnt++);
            StarSingleTon.Instance.zName = reader.GetString(cnt++);
            StarSingleTon.Instance.locationX = reader.GetFloat(cnt++);
            StarSingleTon.Instance.locationY = reader.GetFloat(cnt++);
            StarSingleTon.Instance.locationZ = reader.GetFloat(cnt++);
            StarSingleTon.Instance.zOpen = reader.GetBoolean(cnt++);
            StarSingleTon.Instance.zFind = reader.GetBoolean(cnt++);
            StarSingleTon.Instance.needPE = reader.GetInt32(cnt++);
            StarSingleTon.Instance.nowPE = reader.GetInt32(cnt++);
            StarSingleTon.Instance.zActive = reader.GetBoolean(cnt++);

            cnt = 0;
        }
        cnt = 0;
        reader.Close();
        reader = null;

        StarSingleTon.Instance.setMainText();
        StarSingleTon.Instance.setPointlight();

    }


    public void UpdateQuery(string ShipQuery)
    {
        dbcmd.CommandText = ShipQuery;
        dbcmd.ExecuteNonQuery();

        StarStart();

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
