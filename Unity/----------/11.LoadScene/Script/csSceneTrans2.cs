using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;
using UnityEditor.SceneManagement;
using UnityEditor;


public class csSceneTrans2 : MonoBehaviour {

	public void SceneTrans2_1(){
		SceneManager.LoadScene ("03-Scene2-1");
	}
	public void SceneTrans2_2(){
		SceneManager.LoadScene ("04-Scene2-2");
	}

	void Awake(){
//		Debug.Log ("Awake : " + EditorApplication.currentScene);
		Debug.Log ("Awake : " + EditorSceneManager.GetSceneByName(this.gameObject.scene.name));
	}

	void OnEnable(){
//		Debug.Log ("OnEnable : " + EditorApplication.currentScene);
		Debug.Log ("OnEnable : " + EditorSceneManager.GetSceneByName(this.gameObject.scene.name));
	}

	void Start(){
//		Debug.Log ("Start : " + EditorApplication.currentScene);
		Debug.Log ("Start : " + EditorSceneManager.GetSceneByName(this.gameObject.scene.name));
	}

	void FixedUpdate(){

	}

	void Update(){
	}

	void OnGUI(){
	}
	void OnDisable(){
//		Debug.Log("OnDisable : "+EditorApplication.currentScene);
		Debug.Log ("OnDisable : " + EditorSceneManager.GetSceneByName(this.gameObject.scene.name));
							}
	void OnDestroy(){
//		Debug.Log("OnDestroy : "+EditorApplication.currentScene);
		Debug.Log ("OnDestroy : " + EditorSceneManager.GetSceneByName(this.gameObject.scene.name));
	}




}
