using UnityEngine;
using System.Collections;

public class csCoroutine2 : MonoBehaviour {

	//wait until the end at job?

	public string url;
	WWW www;

	bool isDownloading = false;

	IEnumerator Start(){
		www = new WWW (url);
		isDownloading = true;
		yield return www;
		isDownloading = false;
		Debug.Log ("download completed!");
	}

	void Update(){
		if (isDownloading)
			Debug.Log (www.progress);
	}



}
