using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;
using UnityEngine.UI;


public class csRetry : MonoBehaviour {

	void Start(){
		Debug.Log ("asdf");
	}

	public void reTry(){
		Debug.Log ("click");
		SceneManager.LoadScene ("Game");
	}
		

}
