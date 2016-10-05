using UnityEngine;
using System.Collections;

public class TitleLogoMovement : MonoBehaviour {

    public GameObject btnGuestLogin;
    public GameObject btnFacebookLogin;

    Vector3 titleScale;

	// Use this for initialization
	void Start () {
        titleScale = transform.localScale;

        StartCoroutine(Move());
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    IEnumerator Move()
    {
        while(titleScale.x > 1)
        {
            titleScale.x -= 0.05f;
            titleScale.y -= 0.05f;

            transform.localScale = titleScale;
            yield return new WaitForEndOfFrame();
        }

        yield return new WaitForSeconds(0.8f);

        Vector3 tmp = btnGuestLogin.transform.localScale;

        for(int i =0; i < 10; i++)
        {
            tmp.y += 0.1f;
            btnGuestLogin.transform.localScale = tmp;
            btnFacebookLogin.transform.localScale = tmp;
            yield return new WaitForEndOfFrame();
        }
    }
}
