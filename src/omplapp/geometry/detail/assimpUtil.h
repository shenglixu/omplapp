/*********************************************************************
* Rice University Software Distribution License
*
* Copyright (c) 2010, Rice University
* All Rights Reserved.
*
* For a full description see the file named LICENSE.
*
*********************************************************************/

/* Author: Ioan Sucan */

#ifndef OMPLAPP_GEOMETRY_DETAIL_ASSIMP_UTIL_
#define OMPLAPP_GEOMETRY_DETAIL_ASSIMP_UTIL_

#include <assimp.hpp>
#include <assimp.h>
#include <aiScene.h>
#include <aiPostProcess.h>
#include <ompl/base/spaces/RealVectorBounds.h>
#include <vector>

namespace ompl
{
    namespace app
    {

        /// @cond IGNORE
        /** \brief Utilitiy functions for processing imported scenes */
        namespace scene
        {

            void inferBounds(base::RealVectorBounds &bounds, const std::vector<aiVector3D> &vertices, double multiply = 1.1, double add = 0.0);
            void extractTriangles(const aiScene *scene, std::vector<aiVector3D> &triangles);
            void extractVertices(const aiScene *scene, std::vector<aiVector3D> &vertices);
            double shortestEdge(const aiScene *scene);
            void sceneCenter(const aiScene *scene, aiVector3D &center);
        }
        /// @endcond
    }
}
#endif