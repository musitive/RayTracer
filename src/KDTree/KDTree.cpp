#include "KDTree.h"
#define DIMENSIONS 3
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2        // @todo: Replace with an enum

// Expands the bounding box of a node to include the bounding boxes of its children.
void KDTree::KDTreeNode::expandNodeBoundingBox() {
    if (left) box.expand(left->box);
    if (right) box.expand(right->box);
}

// Determines if a ray intersects the left bounding box of a node.
bool KDTree::KDTreeNode::doesRayIntersectLeft(const Ray &ray) const {
    return left && left->box.doesIntersect(ray);
}

// Determines if a ray intersects the right bounding box of a node.
bool KDTree::KDTreeNode::doesRayIntersectRight(const Ray &ray) const {
    return right && right->box.doesIntersect(ray);
}

// Recursively builds the KD tree from a vector of actors, sorting them by axis at each level of the tree.
KDTree::KDTreeNode* KDTree::buildTree(std::vector<AbstractObject*> &actors, const int &depth) {
    if (actors.empty()) return nullptr;     // Base case

    int axis = depth % DIMENSIONS;
    sortByAxis(actors, axis);

    // Find the median and split the actors into left and right vectors
    int median = actors.size() / 2;
    std::vector<AbstractObject*>::iterator median_it = actors.begin() + median;
    std::vector<AbstractObject*> left_actors(actors.begin(), median_it);
    std::vector<AbstractObject*> right_actors(median_it + 1, actors.end());

    // Create a new node with the median actor
    KDTreeNode* node = new KDTreeNode(actors[median]);
    node->left = buildTree(left_actors, depth + 1);
    node->right = buildTree(right_actors, depth + 1);
    node->expandNodeBoundingBox();

    return node;
}

// Sorts a vector of actors by the center of their bounding boxes along a specified axis.
void KDTree::sortByAxis(std::vector<AbstractObject*> &actors, const int &axis) {
    std::sort(actors.begin(), actors.end(),
        [axis](AbstractObject* a, AbstractObject* b)      
        {   // Lambda function to sort actors by axis
            vec3 center_a = a->getBoundingBox().center();
            vec3 center_b = b->getBoundingBox().center();
            return center_a[axis] < center_b[axis];
        }
    );
}

// Serves as the entry point for finding the closest intersection in the KD tree.
void KDTree::findClosestIntersection(const Ray &ray, void *closest_buffer, void *current_buffer) {
    findClosestIntersection(ray, closest_buffer, current_buffer, root);
    return;
}

/**
 * @brief Recursively finds the closest intersection of a ray in the scene, using a KD tree to reduce the
 * number of intersection tests by checking the left and right bounding boxes.
 * 
 * @param ray The ray to cast through the scene.
 * @param closest_buffer A buffer to store the closest intersection to save memory and improve efficiency.
 * @param current_buffer A buffer to store the current intersection to save memory and improve efficiency.
 * @param node The current node in the KD tree.
 * @param current_object The current object that the ray is intersecting, defaults to nullptr.
 */
void KDTree::findClosestIntersection(const Ray &ray, void *closest_buffer, void *current_buffer,
    KDTreeNode *node, AbstractObject *current_object)
{
    if (!node) return;      // Base case

    if (node->obj != current_object) {
        AbstractIntersect* next = IntersectionFactory::create(node->obj, ray, current_buffer);

        if (next->isCloserThan((AbstractIntersect*) closest_buffer))
            memcpy(closest_buffer, current_buffer, sizeof(Reflection));
    }

    // Traverse the KD tree
    if (node->doesRayIntersectLeft(ray))
        findClosestIntersection(ray, closest_buffer, current_buffer, node->left, current_object);
    if (node->doesRayIntersectRight(ray))
        findClosestIntersection(ray, closest_buffer, current_buffer, node->right, current_object);

    return;
}

// Determines if an object is blocked from a light source by another object.
bool KDTree::isObjectBlocked(const Ray &ray, const AbstractObject *current) {
    return isObjectBlocked(ray, current, root);
}

// Recursively determines if an object is blocked from a light source by another object.
bool KDTree::isObjectBlocked(const Ray &ray, const AbstractObject *current, KDTreeNode *node) {
    if (!node) return false;    // Base case

    if (node->obj != current) {
        vec3 p = node->obj->findIntersection(ray);
        if (p != MISS) return true;
    }

    return isObjectBlocked(ray, current, node->left) || isObjectBlocked(ray, current, node->right);
}