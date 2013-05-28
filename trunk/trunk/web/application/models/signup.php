<?php

class Signup extends MY_Model {

    function __construct() {
        parent::__construct();
        $this->table = 'users';
        // Load the Library
    }

    function check_email_availablity() {
        $email = trim($this->input->post('email'));
        $email = strtolower($email);

        $query = $this->db->query('SELECT * FROM users WHERE email="' . $email . '"');

        if ($query->num_rows() > 0)
            return false;
        else
            return true;
    }

    function get_token() {
        $ret = '';
        for ($x = 0; $x < 32; $x++) {
            $ret .= chr(mt_rand(0, 255));
        }

        $token = sha1($ret);

        return $token;
    }

    function validate($token) {
        $this->db->select('*');
        $this->db->from($this->table);
        $this->db->where('token', $token);
        $query = $this->db->get();

        if ($query->num_rows == 1) {
            $this->db->update('users', array('token' => '', 'active' => 1));
            $result = $query->result_array();
            return array('valid' => true, 'id' => $result['0']['id']);
        } else {
            return array('valid' => false, 'id' => 0);
        }
    }

    function update_by_email($email, $token) {
        $this->db->where('email', $email);
        $this->db->update('users', array('token' => $token));
    }

    function get_by_token($token) {
        $this->db->select('*');
        $this->db->from('users');
        $this->db->where('token', $token);
        $query = $this->db->get();
        if ($query->num_rows == 1)
            $this->db->update('users', array('token' => ''));
        return $query->row_array();
    }
    
    function update_user($id, $password){
        $sql = "UPDATE `users` SET `password` = '".$password."' WHERE `id` = '".$id."'";
        $this->db->query($sql);
    }

}

?>
