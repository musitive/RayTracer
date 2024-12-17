#ifndef KD_TREE_H
#define KD_TREE_H

#include "Vec.h"
#include "Ray.h"
#include "BoundingBox.h"
#include "IntersectionFactory.h"
#include <vector>

class KDTree {
    private:
        /**
         * @struct KDTreeNode
         * @brief The KDTreeNode struct is a node in the KD tree. It contains an actor, a bounding box, and pointers
         * to the left and right nodes.
         */
        struct KDTreeNode {
            AbstractObject *obj;
            KDTreeNode *left;
            KDTreeNode *right;
            BoundingBox box;

            KDTreeNode(AbstractObject *obj) : obj(obj), left(nullptr), right(nullptr) {
                box = obj->getBoundingBox();
            }

            void expandNodeBoundingBox();
            bool doesRayIntersectLeft(const Ray &ray) const;
            bool doesRayIntersectRight(const Ray &ray) const;
        };

        KDTreeNode *root;

    public:
        KDTree(std::vector<AbstractObject*> actors) {
            root = buildTree(actors, 0);
        }

        KDTreeNode* buildTree(std::vector<AbstractObject*> &actors, const int &depth);
        void sortByAxis(std::vector<AbstractObject*> &actors, const int &axis);
        void findClosestIntersection(const Ray &ray, void *closest_buffer, void *current_buffer);
        void findClosestIntersection(const Ray &ray, void *closest_buffer, void *current_buffer,
            KDTreeNode *node, AbstractObject *current_object = nullptr);
        bool isObjectBlocked(const Ray &ray, const AbstractObject *current);
        bool isObjectBlocked(const Ray &ray, const AbstractObject *current, KDTreeNode *node);
};

#endif