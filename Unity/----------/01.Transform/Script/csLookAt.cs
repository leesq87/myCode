using UnityEngine;
using System.Collections;

public class csLookAt : MonoBehaviour {

	Transform obj = null;


	// Use this for initialization
	void Start () {

		obj = GameObject.Find ("Cube2").transform;
	
	}
	
	// Update is called once per frame
	void Update () {
	
		transform.LookAt (obj);
	}
}
