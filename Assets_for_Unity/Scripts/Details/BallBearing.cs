using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class BallBearing : Detail
{
    void Start()
    {
        Name = "Опорный ролик";
        Description = "Опорный ролик для мобильной платформфы. Ролик выполнен в виде металлического шара, размещенного в корпусе.";

        pathToFollow = pathToFollow?.GetComponent<PathEditor>();
        if (pathToFollow)
        {
            pathToFollow.transform.position = transform.position;
            countOfDotsInPath = pathToFollow.pathPoints.Count;
        }
    }
}
