using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;

public class csSceneTrans1 : MonoBehaviour {

	public void SceneTrans1_1(){
		//Application.LoadLevel ("01-Scene1-1");
		SceneManager.LoadScene ("01-Scene1-1");
	}

	public void SceneTrans1_2(){
//		Application.LoadLevel ("01-Scene1-2");
		SceneManager.LoadScene ("01-Scene1-2");
	}



}
