#ifndef KD_TREE_H
#define KD_TREE_H

#include "Vec.h"
#include "Ray.h"
#include "BoundingBox.h"
#include "AbstractIntersect.h"
#include "AbstractObject.h"
#include "MissedIntersect.h"
#include "ReflectionIntersect.h"
#include "DiffuseIntersect.h"
#include <vector>


class IntersectionFactory {
    public:
        static AbstractIntersection* create(AbstractObject* obj, const Ray& ray, void* buffer) {
            Point3D p = obj->findIntersection(ray);

            if (p == MISS)
                return new (buffer) Miss(obj, ray);
            else if (obj->getMaterial()->isReflective)
                return new (buffer) Reflection(obj, ray, p);
            else
                return new (buffer) Absorption(obj, ray, p);
        }

        static AbstractIntersection* createMissed(void* buffer) {
            return new (buffer) Miss(nullptr, Ray());
        }
};

struct KDTreeNode {
    AbstractObject* actor;
    KDTreeNode* left;
    KDTreeNode* right;
    BoundingBox box;

    KDTreeNode(AbstractObject* actor) : actor(actor), left(nullptr), right(nullptr) {
        box = actor->getBoundingBox();
    }
};

class KDTree {
public:
    KDTreeNode* root;

    KDTree(vector<AbstractObject*> actors) {
        root = buildTree(actors, 0);
    }

    KDTreeNode* buildTree(vector<AbstractObject*>& actors, int depth) {
        if (actors.empty()) return nullptr;

        // Sort actors based on the current axis
        int axis = depth % 3;
        sort(actors.begin(), actors.end(), [axis](AbstractObject* a, AbstractObject* b) {
            return a->getBoundingBox().center()[axis] < b->getBoundingBox().center()[axis];
        });

        int median = actors.size() / 2;
        KDTreeNode* node = new KDTreeNode(actors[median]);

        vector<AbstractObject*> leftActors(actors.begin(), actors.begin() + median);
        vector<AbstractObject*> rightActors(actors.begin() + median + 1, actors.end());

        node->left = buildTree(leftActors, depth + 1);
        node->right = buildTree(rightActors, depth + 1);

        // Calculate the bounding box for the current node
        node->box = actors[median]->getBoundingBox();
        if (node->left) node->box.expand(node->left->box);
        if (node->right) node->box.expand(node->right->box);

        return node;
    }

    AbstractIntersection* findClosestIntersection(const Ray& ray, AbstractObject* reflected_object, void* closest_buffer, KDTreeNode* node, AbstractIntersection* closest, void* buffer) {
        if (!node) return closest;

        if (node->actor != reflected_object) {
            AbstractIntersection* next = IntersectionFactory::create(node->actor, ray, buffer);
            if (next->isCloserThan(closest)) {
                memcpy(closest_buffer, buffer, sizeof(Reflection));
            }
        }

        // Traverse the KD tree
        if (node->left && node->left->box.doesIntersect(ray)) {
            closest = findClosestIntersection(ray, reflected_object, closest_buffer, node->left, closest, buffer);
        }
        if (node->right && node->right->box.doesIntersect(ray)) {
            closest = findClosestIntersection(ray, reflected_object, closest_buffer, node->right, closest, buffer);
        }

        return closest;
    }
};

#endif