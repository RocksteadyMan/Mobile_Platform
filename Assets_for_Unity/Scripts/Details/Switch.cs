using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class Switch : Detail
{
    void Start()
    {
        Name = "Выключатель питания";
        Description = "Замыкает цепь, тем самым подключая или отключая питание от аккумулятора.";

        pathToFollow = pathToFollow?.GetComponent<PathEditor>();
        if (pathToFollow)
        {
            pathToFollow.transform.position = transform.position;
            countOfDotsInPath = pathToFollow.pathPoints.Count;
        }
    }
}
