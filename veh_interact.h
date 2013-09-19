#ifndef _VEH_INTERACT_H_
#define _VEH_INTERACT_H_

#include <vector>
#include "output.h"
#include "inventory.h"

enum sel_types {
  SEL_NULL, SEL_JACK
};

class vehicle;
class game;

class veh_interact
{
public:
    int cursor_x;
    int cursor_y;
    int ddx;
    int ddy;
    int sel_vpart_info;
    struct vehicle_part *sel_vehicle_part;
    char sel_cmd; //Command currently being run by the player
    int sel_type;
private:
    int cpart;
    int page_size;
    WINDOW *w_grid;
    WINDOW *w_mode;
    WINDOW *w_msg;
    WINDOW *w_disp;
    WINDOW *w_parts;
    WINDOW *w_stats;
    WINDOW *w_list;

    int winw1;
    int winw2;
    int winh1;
    int winh2;
    int winw12;
    int winw3;
    int winh3;
    int winh23;
    int winx1;
    int winx2;
    int winy1;
    int winy2;

    vehicle *veh;
    game *g;
    bool has_wrench;
    bool has_welder;
    bool has_hacksaw;
    bool has_jack;
    bool has_siphon;
    bool has_wheel;
    inventory crafting_inv;

    int part_at (int dx, int dy);
    void move_cursor (int dx, int dy);
    int cant_do (char mode);

    void do_install(int reason);
    void do_repair(int reason);
    void do_refill(int reason);
    void do_remove(int reason);
    void do_rename(int reason);
    void do_siphon(int reason);
    void do_tirechange(int reason);
    void do_drain(int reason);

    void display_veh ();
    void display_stats ();
    void display_mode (char mode);
    void display_list (int pos);

    /* Vector of all vpart TYPES that can be mounted in the current square.
     * Can be converted to a vector<vpart_info>.
     * Updated whenever the cursor moves. */
    std::vector<int> can_mount;

    /* Vector of vparts in the current square that can be repaired. Strictly a
     * subset of parts_here.
     * Can probably be removed entirely, otherwise is a vector<vehicle_part>.
     * Updated whenever parts_here is updated.
     */
    std::vector<int> need_repair;

    /* Vector of all vparts that exist on the vehicle in the current square.
     * Can be converted to a vector<vehicle_part>.
     * Updated whenever the cursor moves. */
    std::vector<int> parts_here;

    /* Refers to the fuel tank (if any) in the currently selected square. */
    struct vehicle_part *ptank;

    /* Refers to the wheel (if any) in the currently selected square. */
    struct vehicle_part *wheel;

    /* Whether or not the player can refuel the vehicle. Probably doesn't need
     * to be precalculated, but can be kept around harmlessly enough. */
    bool has_fuel;
public:
    veh_interact ();
    void exec (game *gm, vehicle *v, int x, int y);
};

void complete_vehicle (game *g);

#endif
