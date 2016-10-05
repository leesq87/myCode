using UnityEngine;
using System.Collections;
using System.IO;
using UnityEngine.UI;
using System.Collections.Generic;
using System.Text;


public class TextScript : MonoBehaviour
{

    public string textFileName;
    public float sec;
    public Text textNaeyoung;
    public Text textName;
    public StreamReader sr;
    public bool standby;
    int count;
    int prize;

    public GameObject TextPanal;
    public List<string> line = new List<string>();

    private TextAsset ta;
    private string s;
    private int lin;


    public Text txt1;
    public Text txt2;
    public Text txt3;
    public Text txt4;

    
    void Start()
    {
        txt1 = GameObject.Find("UI/Main/txt1").GetComponent<Text>();
        txt2 = GameObject.Find("UI/Main/txt2").GetComponent<Text>();
        txt3 = GameObject.Find("UI/Main/txt3").GetComponent<Text>();
        txt4 = GameObject.Find("UI/Main/txt4").GetComponent<Text>();

        standby = true;

        if (Application.platform == RuntimePlatform.Android)
        {
            txt4.text = (Application.persistentDataPath + "/" + textFileName + ".txt").ToString();
            lin = 0;
            txt3.text = (Application.dataPath + "/" + textFileName + ".txt").ToString();

            //ta = Resources.Load<TextAsset>(Application.persistentDataPath + "/" + textFileName ) as TextAsset;
            //s = ta.text;
            //ta = Resources.Load(textFileName, typeof(TextAsset)) as TextAsset;
            //s = ta.text;
            sr = new StreamReader
                (new FileStream("URI=File:"+Application.persistentDataPath + "/" + textFileName + ".txt",FileMode.Open));

            txt1.text = sr.ToString();
            txt2.text = ta.text.ToString();


        }
        else
        {
            //sr = new StreamReader
            //    (new FileStream(Application.dataPath + "/06.Res/Text/" + textFileName + ".txt", FileMode.Open));

            sr = new StreamReader
                (new FileStream(Application.streamingAssetsPath + "/" + textFileName + ".txt", FileMode.Open));
            count = 0;
            prize = 0;
            readLine();
            txt1.text = "bbbbb";
            txt2.text = sr.ToString();
            txt3.text = (Application.streamingAssetsPath + "/" + textFileName + ".txt").ToString();
        }


        TextPanal.SetActive(false);
    }

    public void readLine()
    {
        while (!sr.EndOfStream)
        {
            line.Add(sr.ReadLine().ToString());
            count++;
        }

    }

    //순서대로 출력
    public void Print()
    {
        if (standby)
        {
            TextPanal.SetActive(true);
            StartCoroutine("textprint");
        }
    }

    IEnumerator textprint()
    {
        if (Application.platform == RuntimePlatform.Android)
        {
            standby = false;
            textName.text = textNaeyoung.text = string.Empty;
            int cnt = 0;
            char[] c = division(s);

            for (cnt = 0; cnt < c.Length; cnt++)
            {
                textNaeyoung.text += c[cnt].ToString();
                yield return new WaitForSeconds(sec);
            }
        }
        else
        {

            standby = false;
            textName.text = textNaeyoung.text = string.Empty;
            int cnt = 0;

            char[] c = line[prize++].ToCharArray();
            if (prize >= count)
            {
                prize = 0;
            }
            for (cnt = 0; cnt < c.Length; cnt++)
            {

                textNaeyoung.text += c[cnt].ToString();

                if (c[cnt] == '\n')
                    break;
                yield return new WaitForSeconds(sec);
            }
        }

        StartCoroutine("textPanalFalse");
        //standby = true;
    }

    IEnumerator textPanalFalse()
    {
        yield return new WaitForSeconds(1.5f);
        TextPanal.SetActive(false);
        standby = true;
    }

    char[] division(string script)
    {
        char[] c = script.ToCharArray();
        script = string.Empty;
        char[] sct = string.Empty.ToCharArray();

        for (int i = lin; i < c.Length; i++)
        {
            if (c[i] == '\r')
            {
                lin = i + 2;
                sct = script.ToCharArray();
                break;
            }
        }

        return sct;
    }

    //random text 출력
    //public void Print()
    //{
    //    if (standby)
    //    {
    //        prize = Random.Range(0, count-1);

    //        StartCoroutine("textprint");
    //    }
    //}

    //IEnumerator textprint()
    //{
    //    standby = false;
    //    textName.text = textNaeyoung.text = string.Empty;
    //    int cnt = 0;

    //    char[] c = line[prize].ToCharArray();
    //    for (cnt = 0; cnt < c.Length; cnt++)
    //    {

    //        textNaeyoung.text += c[cnt].ToString();

    //        if (c[cnt] == '\n')
    //            break;
    //        yield return new WaitForSeconds(sec);
    //    }

    //    standby = true;
    //}

}
