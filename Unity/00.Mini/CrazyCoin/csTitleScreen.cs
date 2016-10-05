using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;

public class csTitleScreen : MonoBehaviour {

	public GUISkin skin ;

	private Quaternion originalRotation;

	void Start(){
		originalRotation = transform.localRotation;
	}

	void Update(){

		transform.localRotation =
			Quaternion.AngleAxis (Mathf.Sin (2.0f * Time.deltaTime) * 20.0f, Vector3.up) *
		Quaternion.AngleAxis (Mathf.Sin (2.7f * Time.deltaTime) * 33.3f, Vector3.right) *
		originalRotation;

		transform.parent.localRotation = 
			Quaternion.AngleAxis (Time.deltaTime * 10.0f, Vector3.up) * transform.parent.localRotation;

		if (Input.GetButtonDown ("Jump")) {
			SceneManager.LoadScene ("Main");
		}
	}

	void OnGUI(){
		GUI.skin = skin;

		int sw = Screen.width;
		int sh = Screen.height;

		GUI.Label (new Rect (0, 0.6f * sh, sw, 0.4f * sh), "PRESS SPACE TO START", "title");
	}


}
