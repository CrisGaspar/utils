require 'set'

class TreeNode
    attr_accessor :val, :left, :right 
    attr_reader :id

    @@id = 0

    def self.nextid
        @@id += 1
        @@id
    end

    def initialize(val: nil, left: nil, right: nil, vals: [])
        @val, @left, @right = val, left, right
        @id = TreeNode.nextid
        build_tree(vals: vals)
    end

    def build_tree(vals: vals)
        vals.each do |val|
            insert(val) 
        end
    end

    def insert(val)
        puts("Val: #{val}")
        if @val.nil?
            # empty tree
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
        func.call(self)
        @right.in_order(func) unless @right.nil?
    end

    def pre_order(func)
        func.call(self)
        @left.pre_order(func) unless @left.nil?
        @right.pre_order(func) unless @right.nil?
    end

    def post_order(func)
        @left.post_order(func) unless @left.nil?
        @right.post_order(func) unless @right.nil?
        func.call(self)
    end

    def bfs(func)
        visited = Set.new
        nodes = []
        nodes << self unless visited.include?(self.id)
        nodes << @left unless @left.nil? or visited.include?(@left.id)
        nodes << @right unless @right.nil? or visited.include?(@right.id)

        while !nodes.empty? do
            cur_node = nodes.shift
            func.call(cur_node) unless visited.include?(cur_node.id)
            visited.add(cur_node.id)
            nodes << cur_node.left unless cur_node.left.nil? or visited.include?(cur_node.left.id)
            nodes << cur_node.right unless cur_node.right.nil? or visited.include?(cur_node.right.id)
        end
    end

    def dfs(func, visited = Set.new)
        @left.dfs(func, visited) unless @left.nil? or visited.include?(@left.id)
        @right.dfs(func, visited) unless @right.nil? or visited.include?(@right.id)
        unless visited.include?(self.id) 
            func.call(self)
            visited.add(self.id)
        end
    end
end

vals = [1, -1, 0, 10, 8, 2, 9, 5]
t = TreeNode.new(vals: vals)
print_node = lambda { |node| puts(node.val) }

t.in_order(print_node)
t.pre_order(print_node)
t.post_order(print_node)
t.bfs(print_node)
t.dfs(print_node)
