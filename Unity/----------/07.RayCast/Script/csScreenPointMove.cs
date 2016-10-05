using UnityEngine;
using System.Collections;

public class csScreenPointMove : MonoBehaviour {

	void Update(){
		if (Input.GetButtonUp ("Fire1")) {
			Ray ray = Camera.main.ScreenPointToRay (Input.mousePosition);
			RaycastHit hit;

			if (Physics.Raycast (ray, out hit)) {
				Vector3 newPos = new Vector3 (hit.point.x, transform.position.y, hit.point.z);

				transform.position = newPos;
			}
		}
	}


}
