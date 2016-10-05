using UnityEngine;
using System.Collections;

public class lakescript : MonoBehaviour {

    public static int ActiveFalseTime  ;

    void Start()
    {
        ActiveFalseTime = 0;
    }

    void Update()
    {
        ActiveFalseTime++;
        if(ActiveFalseTime >= 60)
        {
            this.gameObject.SetActive(false);
        }
    }
}
