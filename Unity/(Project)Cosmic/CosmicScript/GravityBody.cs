using UnityEngine;
using System.Collections;

public class GravityBody : MonoBehaviour {

	public GravityAttractor attractor;
	private Transform myTransform;

	void Start () 
	{
		myTransform = transform;
        GetComponent<Rigidbody>().constraints = RigidbodyConstraints.FreezeRotation;
        GetComponent<Rigidbody>().useGravity = false;

    }
	
	void Update () 
	{
		attractor.Attract (myTransform);
	}
}
