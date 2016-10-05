using UnityEngine;
using System.Collections;

public class csRandom : MonoBehaviour {

	void Start(){
		int randomSeedS;
		randomSeedS = (int)System.DateTime.Now.Ticks;
		Random.seed = randomSeedS;

		//Random.Range (<=,<)
		int randomX = Random.Range (5, 10);
		Debug.Log ("integer :" + randomX);

		float randomY = Random.Range (5.0f, 10.0f);
		Debug.Log ("float :" + randomY);

		//range limit
		// if now number more bigger maximum number, than print maximum num
		// if more little minmum num, than print minmum

		int myVal = 10;
		float nLimit = Mathf.Clamp (myVal, 1, 5);
		Debug.Log ("Clamps :" + nLimit);
	}




}
