using UnityEngine;
using System.Collections;

public class csMove3 : MonoBehaviour {

	float speed = 20;


	// Update is called once per frame
	void Update () {

		float h = Input.GetAxis ("Horizontal");
		float v = Input.GetAxis ("Vertical");

		h = h * speed * Time.deltaTime;
		v = v * speed * Time.deltaTime;

		transform.Translate (Vector3.right * h);
		transform.Translate (Vector3.forward * v);


	}


	void FixedUpdate(){
		if(Input.GetButtonDown("Jump")){
			GetComponent<Rigidbody> ().velocity = new Vector3 (0, 5, 0);
		}
	}

}
