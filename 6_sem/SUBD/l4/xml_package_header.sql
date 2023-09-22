CREATE TYPE xml_record IS TABLE OF VARCHAR2(1000);

/

CREATE OR REPLACE PACKAGE xml_package AS
    FUNCTION extract_xml_value(
        xml_string IN VARCHAR, 
        xpath_string IN VARCHAR)
    RETURN xml_record;
    
    FUNCTION extract_inner_xml(
        xml_string IN VARCHAR, 
        xpath_string IN VARCHAR)
    RETURN xml_record;
    
    FUNCTION get_first_value(current_record IN xml_record)
    RETURN VARCHAR;
    
    FUNCTION get_select_string(xml_string IN VARCHAR)
    RETURN VARCHAR;
    
    FUNCTION get_where_string(xml_string IN VARCHAR)
    RETURN VARCHAR;
    
    FUNCTION get_insert_string(xml_string IN VARCHAR) 
    RETURN VARCHAR;
    
    FUNCTION get_update_string(xml_string IN VARCHAR) 
    RETURN VARCHAR;
    
    FUNCTION get_delete_string ( xml_string IN VARCHAR)
    RETURN VARCHAR;
    
    FUNCTION get_drop_string(xml_string IN VARCHAR) 
    RETURN VARCHAR;
    
    FUNCTION get_create_string(xml_string IN VARCHAR) 
    RETURN VARCHAR;
    
    FUNCTION process_xml_select(xml_string IN VARCHAR)
    RETURN SYS_REFCURSOR;
    
    FUNCTION generate_auto_increment (
        table_name IN VARCHAR, 
        pk_name IN VARCHAR) 
    return VARCHAR;
    
    PROCEDURE process_xml_dml(xml_string IN VARCHAR);
END xml_package;

/