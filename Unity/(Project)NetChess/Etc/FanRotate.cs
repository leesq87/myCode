using UnityEngine;
using System.Collections;

public class FanRotate : MonoBehaviour {

    Vector3 fanDefaultRotation;

	// Use this for initialization
	void Start () {
        fanDefaultRotation = transform.rotation.eulerAngles;
    }
	
	// Update is called once per frame
	void Update () {
	if(fanDefaultRotation.z >= 0 && fanDefaultRotation.z < 360)
        {
            fanDefaultRotation.z += 30 * Time.deltaTime;
            transform.rotation = Quaternion.Euler(fanDefaultRotation);
        }
    else
        {
            fanDefaultRotation.z = 0;
        }
	}
}
