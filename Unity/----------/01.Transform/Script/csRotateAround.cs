using UnityEngine;
using System.Collections;

public class csRotateAround : MonoBehaviour {

	Transform obj = null;


	// Use this for initialization
	void Start () {
	
		obj = GameObject.Find ("Cube1").transform;
	}
	
	// Update is called once per frame
	void Update () {
	
		//rotate aruound1
		//transform.RotateAround(Vector3.zero,Vector3.up,40*Time.deltaTime);


		//rotate aruond2
		transform.RotateAround(obj.position,Vector3.up,40*Time.deltaTime);

		transform.LookAt (obj);

	}
}
