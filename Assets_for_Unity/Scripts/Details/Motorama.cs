using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class Motorama : Detail
{
    void Start()
    {
        Name = "Моторама";
        Description = "Предназначена для фиксации двигателей. Имеет отверстие для установки муфты.";

        pathToFollow = pathToFollow?.GetComponent<PathEditor>();
        if (pathToFollow)
        {
            pathToFollow.transform.position = transform.position;
            countOfDotsInPath = pathToFollow.pathPoints.Count;
        }
    }
}
