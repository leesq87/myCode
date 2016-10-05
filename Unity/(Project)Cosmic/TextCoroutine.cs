using UnityEngine;
using System.Collections;
using System.IO;
using UnityEngine.UI;
using System.Collections.Generic;
using System.Text;

public class TextCoroutine : MonoBehaviour {

    public float sec;
    public Text textContent;
    public Text textName;
    public bool standby;
    int count=0;
    int prize;

    public GameObject TextPanal;
    public List<string> line = new List<string>();


    void Start()
    {
        prize = 0;
        standby = true;
        count = line.Count;

        TextPanal.SetActive(false);


    }


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
        standby = false;
        textName.text = textContent.text = string.Empty;
        int cnt = 0;

        char[] c = line[prize++].ToCharArray();
        if (prize >= count)
        {
            prize = 0;
        }
        for (cnt = 0; cnt < c.Length; cnt++)
        {

        textContent.text += c[cnt].ToString();

           if (c[cnt] == '\n')
               break;
           yield return new WaitForSeconds(sec);
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
