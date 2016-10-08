using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public enum LocationState{
	Disabled,
	TimedOut,
	Failed,
	Enabled
}

public class NewGPSScript : MonoBehaviour {
	public float targetLat;
	public float dLon;
	private Gyroscope gyro;

	public Text mylatitude;
	public Text mylongitude;

	// Approximate radius of the earth (in kilometers)
	const float EARTH_RADIUS = 6371;
	private LocationState state;
	// Position on earth (in degrees)
	private float latitude;
	private float longitude;

	// Use this for initialization
	IEnumerator Start () {

		state = LocationState.Disabled;
		latitude = 0f;
		longitude = 0f;

		if(Input.location.isEnabledByUser){
			Input.location.Start();
			int waitTime = 15;
			while(Input.location.status == LocationServiceStatus.Initializing && waitTime > 0){
				yield return new WaitForSeconds(1);
				waitTime--;
			}
			if(waitTime == 0){
				state = LocationState.TimedOut;
			}else if(Input.location.status == LocationServiceStatus.Failed){
				state = LocationState.Failed;
			}else{
				state = LocationState.Enabled;
				latitude = Input.location.lastData.latitude;
				longitude = Input.location.lastData.longitude;

				mylatitude.text = "" + latitude;
				mylongitude.text = "" + longitude;
			}
		}


	}

	/*
	float bearingPointer(ref float lastLatitude,ref float lastLongitude){

		float newLatitude = Input.location.lastData.latitude;
		float newLongitude = Input.location.lastData.longitude;

		targetLat = 37.538839f;
		dLon = 127.124065f - newLongitude;

		var y = Mathf.Sin(dLon * Mathf.Deg2Rad) * Mathf.Cos(targetLat * Mathf.Deg2Rad);
		var x = Mathf.Cos(newLatitude * Mathf.Deg2Rad) * Mathf.Sin(targetLat * Mathf.Deg2Rad) - Mathf.Sin(newLatitude * Mathf.Deg2Rad) * Mathf.Cos(targetLat * Mathf.Deg2Rad) * Mathf.Cos(dLon * Mathf.Deg2Rad);
		var bearing = ((Mathf.Atan2(y,x)*(180.0f/Mathf.PI)) + 360.0f) % 360.0f;

		return bearing;
	}

	
	// Update is called once per frame
	void Update () {
		if(state == LocationState.Enabled){
			//float deltaDistance = bearingPointer(ref latitude,ref longitude);
			transform.eulerAngles = new Vector3(0f, 0f, Mathf.MoveTowardsAngle(transform.localEulerAngles.z, Input.compass.trueHeading + bearingPointer(ref latitude,ref longitude), 180.0f));
		
		}
	}
	*/
}