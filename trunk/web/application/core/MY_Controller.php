<?php

class MY_Controller extends CI_Controller {

    public $layout;

    public function __construct() {
        parent::__construct();
        $this->load->library('login');
        $this->load->model('user');
        $this->load->helper('url');
        $this->layout = 'layouts/master';
    }

    public function get_login_info() {
        if ($this->login->validate_session()) {
            $data['is_logged'] = 1;
            $data['id'] = $this->login->get_id();
            $result = $this->user->find_by_id($data['id']);
            $data['name'] = $result['name'];
        } else {
            $data['is_logged'] = 0;
            $data['id'] = 0;
            $data['name'] = 'name';
        }
        return $data;
    }

}