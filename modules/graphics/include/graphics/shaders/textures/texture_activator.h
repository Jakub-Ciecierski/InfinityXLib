#ifndef PROJECT_TEXTURE_ACTIVATOR_H
#define PROJECT_TEXTURE_ACTIVATOR_H

namespace ifx {

/**
 * Singleton, keeping track of texture activation id's.
 * Making sure that each texture is actived with unique ID per rendering pass.
 */
class TextureActivator {
public:
    static TextureActivator &GetInstance();

    ~TextureActivator();

    /**
     * Local id is used per single rendering pass of a single mesh.
     */
    int GetNextLocalID();

    /**
     * Global ID is reserved for Global textures that are used between many
     * passes, e.g. shadow_maping is used in every scene object.
     */
    int GetNextGlobalID();

    /**
     * Needs to be called after rendering pass of a single mesh.
     */
    void ResetLocal();

    void ResetGlobal();
private:
    TextureActivator();

    const int local_id_start_;
    const int global_id_start_;

    int local_id_;
    int global_id_;
};
}

#endif //PROJECT_TEXTURE_ACTIVATOR_H
