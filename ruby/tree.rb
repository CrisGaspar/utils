class TreeNode
    attr_accessor :val, :left, :right 
    attr_reader :visited

    def initialize(val: nil, left: nil, right: nil, vals: [])
        @val, @left, @right = val, left, right
        @visited = false
        self.build_tree(vals: vals)
    end

    // TODO: private
    def build_tree(vals: [])
        vals.each do |val|
            self.insert(val) 
        end
    end

    // TODO: private
    def insert(val)
        if @val.nil?
            @val = val
            return
        elsif @val == val
            return
        elsif val > @val
            if @right.nil?
                @right = TreeNode.new(val: val)
            else 
                @right.insert(val)
            end
        else
            if @left.nil?
                @left = TreeNode.new(val: val)
            else 
                @left.insert(val)
            end
        end 
    end

    def in_order(func)
        @left.in_order(func) unless @left.nil?
        func(self)
        @right.in_order(func) unless @right.nil?
    end

    def pre_order(func)
        func(self)
        @left.in_order(func) unless @left.nil?
        @right.in_order(func) unless @right.nil?

    end

    def post_order(func)
        @left.in_order(func) unless @left.nil?
        @right.in_order(func) unless @right.nil?
        func(self)
    end

    def bfs(func)
        nodes = []
        nodes << self unless @visited
        nodes << @left unless @left.nil? or @left.visited
        nodes << @right unless @right.nil? or @right.visited

        while nodes. do
            cur_node = nodes.shift
            func(cur_node) unless cur_node.visited?
            cur_node.visited = true
            nodes << cur_node.left unless cur_node.left.nil? or cur_node.left.visited?
            nodes << cur_node.right unless cur_node.right.nil? or cur_node.right.visited?
        end
    end

    def dfs(func)
        @left.dfs(func) unless @left.nil? or @left.visited
        @rigth.dfs(func) unless @right.nil? or @right.visited
        unless @visited 
            func(self)
            @visited = true
        end
    end 
end

t = TreeNode.new(vals: [1, -1, 0, 10, 8, 2, 9, 5])
print_node = lambda { |node| puts(node.val) }
t.in_order(print_node)
