#ifndef DELETE_FUNCTION
#define DELETE_FUNCTION


#include <cstdio>
#include <cstdint>
#include <utility>
#include <switch.h>
#include <math.h>
#include <imgui.h>


#include "json.hpp"
#include "incognito.h"
#include "gui.hpp"
#include "theme.hpp"
#include "incognito.h"
#endif



enum  {Backup,Delete,verify,Import};
int e = 0 ;
bool is_button = false ;
bool result ;
bool backup_flag = false;
bool delete_flag = false;
bool verify_flag = false;
bool import_flag = false;

Incognito incognito;

namespace delete_tian
{
    static inline void display_delete() {

        
        ImGui::RadioButton(Lang::stringtochar("button_backup"_lang), &e, 0); 
        ImGui::RadioButton(Lang::stringtochar("button_delete"_lang), &e, 1); 
        ImGui::RadioButton(Lang::stringtochar("button_verfiy"_lang), &e, 2);
        ImGui::RadioButton(Lang::stringtochar("button_import"_lang), &e, 3);
        
        is_button = ImGui::Button(Lang::stringtochar("select_order"_lang));

        switch (e)
        {
            case Backup:
                
                im::Text(Lang::stringtochar("backup_make_sure"_lang));
                if(is_button)
                {
                    result =  incognito.backup();
                    backup_flag = true;
                    delete_flag = false;
                    verify_flag = false;
                    import_flag = false;
                }
                if(backup_flag)
                {
                    if(result)
                        im::Text(Lang::stringtochar("backup_success"_lang)  );
                    else 
                        im::Text(Lang::stringtochar("backup_fail"_lang));
                }
                break;
                
            case Delete:
                
                im::Text(Lang::stringtochar("delete_make_sure"_lang));
                if(is_button)
                {
                    result = incognito.clean();
                    backup_flag = false;
                    delete_flag = true;
                    verify_flag = false;
                    import_flag = false;
                }
                if(delete_flag)
                {
                    if(result)
                        im::Text(Lang::stringtochar("delete_success"_lang));
                    else 
                        im::Text(Lang::stringtochar("delete_fail"_lang));
                }
                break;
                
            case verify:
                
                im::Text(Lang::stringtochar("verify_make_sure"_lang));
                if(is_button)
                {
                    result = incognito.verify();
                    backup_flag = false;
                    delete_flag = false;
                    verify_flag = true;
                    import_flag = false;
                }
                if(verify_flag)
                {
                    if (result)
                        im::Text(Lang::stringtochar("verify_success"_lang),incognito.serial());
                    else
                        im::Text(Lang::stringtochar("verify_fail"_lang));
                }
                break;
                
            case Import:
                
                im::Text(Lang::stringtochar("import_make_sure"_lang));
                if(is_button)
                {
                    result = incognito.import("sdmc:/backup/prodinfo.bin");
                    backup_flag = false;
                    delete_flag = false;
                    verify_flag = false;
                    import_flag = true;
                }
                if(import_flag)
                {
                    if (result)
                        im::Text(Lang::stringtochar("import_success"_lang),incognito.serial());
                    else 
                        im::Text(Lang::stringtochar("import_fail"_lang));
                }
                break;
            default:
                break;
        }

    } // namespace tian
}