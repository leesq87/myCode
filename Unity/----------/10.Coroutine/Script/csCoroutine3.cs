using UnityEngine;
using System.Collections;

public class csCoroutine3 : MonoBehaviour {

	public string url;
	WWW www;

	IEnumerator Start(){
		www = new WWW (url);
		StartCoroutine ("CheckProgress");
		yield return www;
		Debug.Log ("Download Completed");
	}

	IEnumerator CheckProgress(){
		Debug.Log ("A: " + www.progress);
		while(!www.isDone){
			yield return new WaitForSeconds(0.5f);
			Debug.Log("B" + www.progress);
		}
	}



}
