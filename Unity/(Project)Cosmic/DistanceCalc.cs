using UnityEngine;
using System.Collections;

public class DistanceCalc : MonoBehaviour {

    public GameObject point;
    public GameObject destination;

    float calcResult;

	void Start () {
        
    }
	
	void Update () {
        calcResult = Vector3.Distance(point.transform.position, destination.transform.position);
        Debug.Log(calcResult);
    }
}
