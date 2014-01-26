#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <Phonon/MediaObject>

class SoundManager
{
    public:
        explicit SoundManager();

    static void PlayShoot();
    static void PlayJump();
    static void PlayExplosion();
    static void PlayHitTaken();

private:
    Phonon::MediaObject* _player_shoot;
    Phonon::MediaObject* _player_jump;
    Phonon::MediaObject* _player_explosion;
    Phonon::MediaObject* _player_hit_taken;
};

#endif // SOUNDMANAGER_H
