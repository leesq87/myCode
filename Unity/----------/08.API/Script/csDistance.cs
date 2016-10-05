using UnityEngine;
using System.Collections;

public class csDistance : MonoBehaviour {

	public Transform box1;
	public Transform box2;
	public Transform box3;

	void Start(){

		//calculate betwin two obj
		float distance1 = Vector3.Distance (transform.position, box2.position);
		Debug.Log ("distance1 :" + distance1);

		//second method
		//Vector3.Distance (a,b) is the same as (a -b ).maginitde.
		//whenever obj have front
		float distance2 = (box3.position - transform.position).magnitude;
		Debug.Log ("distance2 :" + distance2);

		//calculate direct
		Vector3 dir = box2.position - transform.position;
		dir.Normalize ();

		//rotation
		transform.eulerAngles = dir;
	}



}
