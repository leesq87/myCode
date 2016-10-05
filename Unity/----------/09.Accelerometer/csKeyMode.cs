using UnityEngine;
using System.Collections;

public class csKeyMode : MonoBehaviour {

	void Update(){
//		transform.rotation *= Quaternion.AngleAxis (Input.GetAxis ("Horizontal") * 30.0f * -1 * Time.deltaTime, Vector3.forward);

//		transform.rotation *= Quaternion.AngleAxis (Input.GetAxis ("Vertical") * 30.0f * -1 * Time.deltaTime, Vector3.left);


		Vector3 dir = Vector3.zero;
//		dir.x = -Input.acceleration.y;
//		dir.z = Input.acceleration.x;


		dir.x = Input.acceleration.y;
		dir.z = -Input.acceleration.x;

		if (dir.sqrMagnitude > 1)
			dir.Normalize ();

		dir *= Time.deltaTime;
		transform.Rotate (dir * 10.0f);
	
	
	
	
	}



}
