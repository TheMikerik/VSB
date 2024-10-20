// ICameraObserver.h
#ifndef ICAMERAOBSERVER_H
#define ICAMERAOBSERVER_H

#include <glm/glm.hpp>

class ICameraObserver {
public:
    virtual ~ICameraObserver() {}
    virtual void onCameraUpdate(const glm::mat4& view, const glm::mat4& projection) = 0;
};

#endif // ICAMERAOBSERVER_H