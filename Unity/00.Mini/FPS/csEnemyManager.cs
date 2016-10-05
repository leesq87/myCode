using UnityEngine;
using System.Collections;

public class csEnemyManager : MonoBehaviour  

{ 

  public GameObject enemy; 

  public float spawnTime = 2.0f;


    int spawnCnt = 1; 

  int maxSpawnCnt = 10; 
   

  float deltaSpawnTime = 0.0f;
    GameObject[] enemyPool; 

  int poolSize = 10; 

  void Start ()  

  { 

    enemyPool = new GameObject[poolSize]; 

    for (int i=0; i<poolSize; ++i) 

    { 

      enemyPool[i] = Instantiate(enemy) as GameObject; 

      enemyPool[i].SetActive(false); 

    } 

  } 
  void Update ()
	{
		if (spawnCnt > maxSpawnCnt)
			return;
		deltaSpawnTime += Time.deltaTime;  

   

		if (deltaSpawnTime > spawnTime) {
             

			deltaSpawnTime = 0.0f; 

    

			for (int i = 0; i < poolSize; i++) { 

				if (enemyPool [i].activeSelf == true)
					continue; 

     

				int x = Random.Range (-20, 20);        

				enemyPool [i].transform.position = new Vector3 (x, 0.1f, 20.0f); 

				enemyPool [i].SetActive (true);  

				enemyPool [i].name = "Enemy_" + spawnCnt;  

				++spawnCnt;  

				break;  


			}
                

		} 

	}
}













/*
public class csEnemyManager : MonoBehaviour {

	public GameObject enemy;
	public float spawnTime =2.0f;
	int spawnCnt =1;
	int maxSpawnCnt = 10;

	float deltaSpawnTime = 0.0f;

	GameObject[] enemyPool;
	int poolSize = 10;

	void Start(){
		enemyPool = new GameObject[poolSize];
		for (int i = 0; i < poolSize; ++i) {
			enemyPool [i] = Instantiate (enemy) as GameObject;
			enemyPool [i].SetActive (false);
		}
	}


	void Update(){

		if (spawnCnt > maxSpawnCnt)
			return;
		
		deltaSpawnTime += Time.deltaTime;
	
		if (deltaSpawnTime > spawnTime) {
			deltaSpawnTime = 0.0f;
			for (int i=0; i<poolSize; i++) {
				if (enemyPool [i].activeSelf == true) {
					continue;
				}

				int x = Random.Range (-20, 20);
				enemyPool [i].transform.position = new Vector3 (x, 0.1f, 20.0f);
				enemyPool [i].SetActive (true);

				enemyPool [i].name = "Enemy_" + spawnCnt;

				++spawnCnt;
				break;
			}
		}


*/