using UnityEngine;
using System.Collections;

public class csRotate1 : MonoBehaviour {

	// Use this for initialization
	void Start () {

		//rotate값 초기화
		transform.eulerAngles = new Vector3 (0,50,0);

		//트 랜 스 폼 rotation 값 회전2
		//rotation은 Quaternion 값으로 대입해 주어야 한다.
		Quaternion target = Quaternion.Euler (0, 100, 0);
		transform.rotation = target;

		//회전
		transform.Rotate(Vector3.up * 90);

	
	}
	

}
