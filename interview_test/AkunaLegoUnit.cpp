
/*
UNITS: 1
a : = sum
INPUTS : 2
CONNECTIONS : 3
input / 0 --a / in / 0
input / 1 --a / in / 1
a / out / 0 --result
VALUES : 3
input / 0 : = 3
input / 1 : = 5
input / 0 : = 7
*/


#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <stack>
#include <list>




// UnitObject is base class for all unit(sum, max....), including special "unit" : input, result
// A common UnitObject can support multi-input port and multi-output port , input and result is a 1:1 unit.
// One income port has only one source, one output port can be mapped to various unit's input port.
// 

class UnitObject
{
public:
    typedef struct _previous_egress_
    {
        std::string id;
        int egress_index;
    }previous_egress_t;

    typedef struct _descendant_ingress_
    {
        std::string id;
        int ingress_index;
    }descendant_ingress_t;

public:
    UnitObject()
        : ingress_param_count(0), egress_param_count(0), unit_type("none"), unit_name(""), unique_id("")
    {
        previous_references.clear();
        egress_values.clear();
    }

    UnitObject(int in, int out, std::string type, std::string name, std::string id)
        : ingress_param_count(in), egress_param_count(out), unit_type(type), unit_name(name), unique_id(id)
    {
        previous_references.clear();
        egress_values.clear();
    }

    virtual ~UnitObject() {}

    // Calculate the output value of unit, and store it in 
    // for input/result unit, set directly 
    virtual int evaluate(std::map<int, int> &ingress_param) { return 0; }





    int get_ingress_param_count() { return ingress_param_count; }
    int get_egress_param_count() { return egress_param_count; }
    std::string &get_unit_type() { return unit_type; }
    std::string &get_unit_name() { return unit_name; }
    std::string &get_unique_id() { return unique_id; }

    int set_next_ref(int index, descendant_ingress_t next)
    {
        if (index < 0)
        {
            return -1;
        }
        descendant_references[index].push_back(next);
        return 0;
    }

    int remove_next_ref(int index, std::string id)
    {
        if (index < 0)
        {
            return -1;
        }
        auto it = descendant_references[index].begin();
        while (it != descendant_references[index].end())
        {
            if (it->id == id)
            {
                descendant_references[index].erase(it);
                break;
            }
        }       
        return 0;
    }

    int set_previous_ref(int index, previous_egress_t previous)
    {
        if (index < 0)
        {
            return -1;
        }
        previous_references[index] = previous;
        return 0;
    }

    std::map<int, previous_egress_t> &get_previous_references() { return previous_references; }
    std::map<int, int> &get_egress_values() { return egress_values; }
    std::map<int, std::list<descendant_ingress_t>> & get_descendant_references() { return descendant_references; }


protected:
    int ingress_param_count;   
    int egress_param_count;
    std::string unit_type;  // sum, mul, input, result ...
    std::string unit_name;  // the name of type instance. for input unit, use "inputX" as name , X is input series num; for result, use "result" as name
    std::string unique_id;  // the global string id for each unit instance.

    // The key of all 3 maps below is ingress/egress port index.
    // In compatible for the case "value has not been set/evaluated" ,just use key-value map instread of vector. 
    std::map<int, previous_egress_t> previous_references; 
    std::map<int, int> egress_values;
    std::map<int, std::list<descendant_ingress_t>> descendant_references; // output port's value can be used by various unit's input, so need a vector to store ref info.
};



class SumUnitObject : public UnitObject
{
public:
    SumUnitObject() {}
    SumUnitObject(std::string name, std::string id) : UnitObject(2, 1, "sum", name, id)
    {
    }
    virtual ~SumUnitObject() {}

    int evaluate(std::map<int, int> &ingress_param)
    {
        if (ingress_param.size() != get_ingress_param_count()
            || ingress_param.count(0) == 0
            || ingress_param.count(1) == 0)
        {
            return -1;
        }
        egress_values.clear();
        egress_values[0] = ingress_param[0] + ingress_param[1];
        return 0;
    }
};

class MaxUnitObject : public UnitObject
{
public:
    MaxUnitObject() {}
    MaxUnitObject(std::string name, std::string id) : UnitObject(2, 1, "max", name, id)
    {
    }
    virtual ~MaxUnitObject() {}

    int evaluate(std::map<int, int> &ingress_param)
    {
        if (ingress_param.size() != get_ingress_param_count()
            || ingress_param.count(0) == 0
            || ingress_param.count(1) == 0)
        {
            return -1;
        }
        egress_values.clear();
        egress_values[0] = ingress_param[0] > ingress_param[1] ? ingress_param[0] : ingress_param[1];
        return 0;
    }
};

class MinUnitObject : public UnitObject
{
public:
    MinUnitObject() {}
    MinUnitObject(std::string name, std::string id) : UnitObject(2, 1, "min", name, id)
    {
    }
    virtual ~MinUnitObject() {}

    int evaluate(std::map<int, int> &ingress_param)
    {
        if (ingress_param.size() != get_ingress_param_count()
            || ingress_param.count(0) == 0
            || ingress_param.count(1) == 0)
        {
            return -1;
        }
        egress_values.clear();
        egress_values[0] = ingress_param[0] < ingress_param[1] ? ingress_param[0] : ingress_param[1];
        return 0;
    }
};

class MulUnitObject : public UnitObject
{
public:
    MulUnitObject() {}
    MulUnitObject(std::string name, std::string id) : UnitObject(2, 1, "mul", name, id)
    {
    }
    virtual ~MulUnitObject() {}

    int evaluate(std::map<int, int> &ingress_param)
    {
        if (ingress_param.size() != get_ingress_param_count()
            || ingress_param.count(0) == 0
            || ingress_param.count(1) == 0)
        {
            return -1;
        }
        egress_values.clear();
        egress_values[0] = ingress_param[0] * ingress_param[1];
        return 0;
    }
};

class NegateUnitObject : public UnitObject
{
public:
    NegateUnitObject() {}
    NegateUnitObject(std::string name, std::string id) : UnitObject(1, 1, "negate", name, id)
    {
    }
    virtual ~NegateUnitObject() {}

    int evaluate(std::map<int, int> &ingress_param)
    {
        if (ingress_param.size() != get_ingress_param_count()
            || ingress_param.count(0) == 0)
        {
            return -1;
        }
        egress_values.clear();
        egress_values[0] = -ingress_param[0];
        return 0;
    }
};

class InputUnitObject : public UnitObject
{
public:
    InputUnitObject() {}
    InputUnitObject(std::string name, std::string id) : UnitObject(1, 1, "input", name, id)
    {
    }
    virtual ~InputUnitObject() {}

    int evaluate(std::map<int, int> &ingress_param)
    {
        if (ingress_param.size() != get_ingress_param_count()
            || ingress_param.count(0) == 0)
        {
            return -1;
        }
        egress_values.clear();
        egress_values[0] = ingress_param[0];
        return 0;
    }
};


class ResultUnitObject : public UnitObject
{
public:
    ResultUnitObject() {}
    ResultUnitObject(std::string name, std::string id) : UnitObject(1, 1, "result", name, id)
    {
    }
    virtual ~ResultUnitObject() {}

    int evaluate(std::map<int, int> &ingress_param)
    {
        if (ingress_param.size() != get_ingress_param_count()
            || ingress_param.count(0) == 0)
        {
            return -1;
        }
        egress_values.clear();
        egress_values[0] = ingress_param[0];
        return 0;
    }
};




class AkunaLegoUnit
{

public:
    AkunaLegoUnit() : input_count(0), is_toplogical_sorted(false)
    {
        /*
        unit_with_two_input["sum"] = sum;
        unit_with_two_input["max"] = max;
        unit_with_two_input["min"] = min;
        unit_with_two_input["mul"] = mul;
        */
        connection_objects.clear();
        unit_name_type_map.clear();

    }

    virtual ~AkunaLegoUnit()
    {
        auto it = connection_objects.begin();
        while (it != connection_objects.end())
        {
            if (it->second)
            {
                delete it->second;
                it->second = nullptr;
            }
        }
        connection_objects.clear();
        unit_name_type_map.clear();

    }


    static AkunaLegoUnit *get_instance()
    {
        // single thread
        if (instance == nullptr)
        {
            instance = new AkunaLegoUnit();
        }
        return instance;
    }

    static std::string get_unique_id(std::string token1, std::string token2, std::string token3)
    {
        std::string unique_id;
        if (token1 == "input")
        {
            unique_id = "0_input" + token3;
        }
        else if (token1 == "result")
        {
            unique_id = "2_result";
        }
        else
        {
            unique_id = "1_" + token1;
        }
        return unique_id;
    }

    // factory method for unit object
    static UnitObject *get_unit_object_instance(std::string token1, std::string token2, std::string token3)
    {
        UnitObject *object = nullptr;
        if (token1 == "input" && token2 == "")
        {
            object = new InputUnitObject(token1, get_unique_id(token1, token2, token3));
        }
        else if (token1 == "result" && token2 == "")
        {
            object = new ResultUnitObject(token1, get_unique_id(token1, token2, token3));
        }
        else
        {
            if (AkunaLegoUnit::get_instance()->unit_name_type_map.count(token1) == 0)
            {
                return nullptr;
            }

            std::string type = AkunaLegoUnit::get_instance()->unit_name_type_map[token1];
            if (type == "sum")
            {
                object = new SumUnitObject(token1, get_unique_id(token1, token2, token3));
            }
            else if (type == "max")
            {
                object = new MaxUnitObject(token1, get_unique_id(token1, token2, token3));
            }
            else if (type == "min")
            {
                object = new MinUnitObject(token1, get_unique_id(token1, token2, token3));
            }
            else if (type == "mul")
            {
                object = new MulUnitObject(token1, get_unique_id(token1, token2, token3));
            }
            else if (type == "negate")
            {
                object = new NegateUnitObject(token1, get_unique_id(token1, token2, token3));
            }
            else
            {
                object = new UnitObject();
            }
        }
        return object;
    }









    static void uint_cb(std::string name, std::string type)
    {
        AkunaLegoUnit::get_instance()->unit_name_type_map[name] = type;
        // std::cout << "unit:" << name << type << std::endl;
        // std::cout << "unit_name_type_map size " << AkunaLegoUnit::get_instance()->unit_name_type_map.size() << std::endl;
    }

    static void input_cb(int num)
    {
        AkunaLegoUnit::get_instance()->input_count = num;
        // std::cout << "input:" << num << std::endl;
        // std::cout << "unit_name_type_map size " << AkunaLegoUnit::get_instance()->unit_name_type_map.size() << std::endl;
    }

    static void connection_cb(std::string first, std::string second, std::string third, std::string forth, std::string fifth, std::string sixth)
    {
        std::cout << "connection_cb called" << std::endl;

        UnitObject::previous_egress_t previous_egress;
        UnitObject::descendant_ingress_t descendant_ingress;
        // general previous_egress info from 1 - 3 param
        if (first == "input" && second == "")
        {
            previous_egress.id = "0_" + first + third;
            previous_egress.egress_index = 0;
        }
        else if (first == "result" && second == "")
        {
            previous_egress.id = "2_" + first;
            previous_egress.egress_index = 0;
        }
        else
        {
            previous_egress.id = "1_" + first;
            previous_egress.egress_index = atoi(third.c_str());
        }

        // general descendant_ingress info from 4 - 6 param
        if (forth == "input" && fifth == "")
        {
            descendant_ingress.id = "0_" + forth + sixth;
            descendant_ingress.ingress_index = 0;
        }
        else if (forth == "result" && fifth == "")
        {
            descendant_ingress.id = "2_" + forth;
            descendant_ingress.ingress_index = 0;
        }
        else
        {
            descendant_ingress.id = "1_" + forth;
            descendant_ingress.ingress_index = atoi(sixth.c_str());
        }

        // if unit object is not exist yet, just new it.
        UnitObject *&former_node = AkunaLegoUnit::get_instance()->connection_objects[previous_egress.id];
        if (former_node == nullptr)
        {
            former_node = get_unit_object_instance(first, second, third);
        }

        UnitObject *&latter_node = AkunaLegoUnit::get_instance()->connection_objects[descendant_ingress.id];
        if (latter_node == nullptr)
        {
            latter_node = get_unit_object_instance(forth, fifth, sixth);
        }

        // set relationship info for both unit object
        former_node->set_next_ref(previous_egress.egress_index, descendant_ingress);

        // if this port has reference an egress port, detach the relationship first.
        if (latter_node->get_previous_references().count(descendant_ingress.ingress_index))
        {
            UnitObject::previous_egress_t temp = latter_node->get_previous_references()[descendant_ingress.ingress_index];
            UnitObject *&object = AkunaLegoUnit::get_instance()->connection_objects[temp.id];
            if (object)
            {
                object->remove_next_ref(temp.egress_index, descendant_ingress.id);
            }
        }

        latter_node->set_previous_ref(descendant_ingress.ingress_index, previous_egress);

    }


    static void value_cb(std::string input, std::string index, std::string value)
    {
        std::cout << "value called" << std::endl;

        // sort all unit object as topological order.
        // only run once when this callback called first time.
        AkunaLegoUnit::get_instance()->topological_sort();

        // set / update new value for input unit object.
        std::string dest_objest_name = get_unique_id("input", "", index);
        UnitObject *&object = AkunaLegoUnit::get_instance()->connection_objects[dest_objest_name];
        if (object == nullptr)
        {
            object = get_unit_object_instance("input", "", index);
        }
        std::map<int, int> in;
        in[0] = atoi(value.c_str());
        object->evaluate(in);

        // Try to evaluate all unit object's output value one by one, by topological order
        // If result object can be evaluate, output it to STDOUT.
        AkunaLegoUnit::get_instance()->evaluate_and_output();
    }



private:

    int topological_sort()
    {
        if (is_toplogical_sorted)
        {
            return 0;
        }
        is_toplogical_sorted = true;

        std::cout << "toplogical_sort called" << std::endl;

        std::stack<std::string> temp_stack;

        std::map<std::string, int> in_count;
        auto it = connection_objects.begin();
        while (it != connection_objects.end())
        {
            in_count[it->first] = it->second->get_previous_references().size();
            it++;
        }

        toplogical_sorted.clear();
        while (true)
        {
            /*
            std::cout << "the in_count vector :";
            for (auto i : in_count)
            {
            std::cout << i.first << " " << i.second << ";";
            }
            std::cout <<std::endl;
            */

            auto iter = in_count.begin();
            while (iter != in_count.end())
            {
                if (iter->second == 0)
                {
                    temp_stack.push(iter->first);
                    iter->second--;
                }
                iter++;
            }
            // there is no more unit to sort
            // or there is a loop in graph
            if (temp_stack.size() == 0)
            {
                break;
            }

            while (!temp_stack.empty())
            {
                //std::cout << "temp_stack.size() :"<< temp_stack.size() <<std::endl;
                std::map<int, std::list<UnitObject::descendant_ingress_t>> &next = connection_objects[temp_stack.top()]->get_descendant_references();

                auto it = next.begin();
                while (it != next.end())
                {
                    //std::cout << "descendant_ingress_t :"<< it->first <<" ";
                    for (auto ele : it->second)
                    {
                        //std::cout << ele.id <<" " << ele.ingress_index << ";";
                        in_count[ele.id]--;
                    }
                    //std::cout <<std::endl;
                    it++;
                }
                toplogical_sorted.push_back(temp_stack.top());
                temp_stack.pop();
            }
        }
        return 0;
    }



    void evaluate_and_output()
    {
        std::cout << "evaluate_and_output called" << std::endl;

        std::cout << "the toplogical_sorted vector :";
        for (auto i : toplogical_sorted)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        std::map<int, int> unit_call_params;

        // evaluate all unit list in topological sort
        // only evaluate the unit which has previous reference
        bool is_previous_param_ready = true;
        for (auto elem : toplogical_sorted)
        {
            is_previous_param_ready = true;
            std::map<int, UnitObject::previous_egress_t> &previous_references = connection_objects[elem]->get_previous_references();
            if (previous_references.size() == 0)
            {
                continue;
            }

            unit_call_params.clear();
            /*
            bool is_previous_param_ready = true;
            if (previous_references.size() == 0)
            {
                is_previous_param_ready = false;
            }
            */

            for (auto pair_elem : previous_references)
            {
                std::map<int, int> &egress_values = connection_objects[pair_elem.second.id]->get_egress_values();
                if (egress_values.count(pair_elem.second.egress_index) == 0)
                {
                    is_previous_param_ready = false;
                    continue;
                }
                unit_call_params[pair_elem.first] = egress_values[pair_elem.second.egress_index];
            }

            if (is_previous_param_ready)
            {
                connection_objects[elem]->evaluate(unit_call_params);
            }

        }

        // if result object can be evaluted , just output it to STDOUT
        std::map<int, int> &result_egress_values = connection_objects["2_result"]->get_egress_values();
        if (result_egress_values.size())
        {
            std::cout << result_egress_values[0] << std::endl;
        }
    }


    static AkunaLegoUnit *instance;

    int input_count;
    std::map<std::string, std::string> unit_name_type_map;

    bool is_toplogical_sorted;
    std::vector<std::string> toplogical_sorted;
    
    std::map<std::string, UnitObject*> connection_objects;


    // std::map<std::string, int> evaluate_map;
    // std::map<std::string, std::map<int, std::string> > connection_map;
    // std::map<std::string, std::function<int(int, int)> > unit_with_two_input;


};

AkunaLegoUnit * AkunaLegoUnit::instance = nullptr;




int main()
{
    input_parser var;
    // AkunaLegoUnit lego_unit;
    var.register_unit_callback(AkunaLegoUnit::uint_cb);
    var.register_input_callback(AkunaLegoUnit::input_cb);
    var.register_connection_callback(AkunaLegoUnit::connection_cb);
    var.register_value_callback(AkunaLegoUnit::value_cb);
    var.process();
    return 0;
}
