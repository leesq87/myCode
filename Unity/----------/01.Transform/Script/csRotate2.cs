using UnityEngine;
using System.Collections;

public class csRotate2 : MonoBehaviour {


	float speed= 50;
	
	// Update is called once per frame
	void Update () {
		float h = Input.GetAxis ("Horizontal");
		float v = Input.GetAxis ("Vertical");

		h = h * speed * Time.deltaTime;
		v = v * speed * Time.deltaTime;	

		//rotate1 
		//transform.Rotate(Vector3.forward*h); // Horizontal -z axis
		//transform.Rotate(Vector3.right*v); // Vertical - x axis

		transform.rotation *= Quaternion.AngleAxis (h, Vector3.forward);
		transform.rotation *= Quaternion.AngleAxis (v, Vector3.right);
	}
}
